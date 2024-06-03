const std = @import("std");

fn compile_and_call_test(filename: []const u8) !bool {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    // compile test
    const source_code = try std.fs.path.join(allocator, &[_][]const u8{ "tests", filename });
    const compiler_process = try std.process.Child.run(.{
        .argv = &[_][]const u8{ "g++", "-fsanitize=address", source_code, "./harness.cc", "-o", "test" },
        .allocator = allocator,
    });
    if (compiler_process.term != .Exited) {
        std.debug.print("error g++ exited abnormally\n", .{});
        return false;
    }
    const compiler_exit_code = compiler_process.term.Exited;
    if (compiler_exit_code != 0) {
        std.debug.print("error g++ non-zero exit code\n", .{});
        std.debug.print("{s}\n", .{compiler_process.stderr});
        return false;
    }

    // run test
    const test_process = try std.process.Child.run(.{
        .argv = &[_][]const u8{"./test"},
        .allocator = allocator,
    });
    if (test_process.term != .Exited) {
        std.debug.print("error ./test exited abnormally\n", .{});
        return false;
    }
    const test_exit_code = test_process.term.Exited;
    if (test_exit_code != 0) {
        std.debug.print("error ./test non-zero exit code\n", .{});
        if (test_process.stderr.len > 0) {
            std.debug.print("{s}\n", .{test_process.stderr});
        }
        return false;
    }
    return true;
}

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    const dir = try std.fs.cwd().openDir("./tests", .{ .iterate = true });
    var walker = try dir.walk(allocator);
    defer walker.deinit();

    var total: u8 = 0;
    var passed: u8 = 0;
    while (try walker.next()) |entry| {
        std.debug.print("running test {s}\n", .{entry.basename});
        const res = try compile_and_call_test(entry.basename);
        std.debug.print("test {s}: {s}\n\n", .{ entry.basename, if (res) "passed" else "failed" });
        if (res) {
            passed += 1;
        }
        total += 1;
    }
    std.debug.print("passed {} out of {} tests\n", .{ passed, total });
    if (passed < total) {
        std.process.exit(1);
    }
}
