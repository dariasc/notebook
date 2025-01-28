#!/usr/bin/env python3
import os
import subprocess
from pathlib import Path

def hash_content(content):
    cmd = "cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6"
    result = subprocess.run(
        cmd,
        input=content,
        shell=True,
        text=True,
        capture_output=True,
        check=True
    )
    return result.stdout.strip()


def process_header_file(input_file: Path, output_file: Path, interval: int = 8) -> None:
    """Process a single header file and generate hashes at specified intervals."""
    # Create output directory if needed
    output_file.parent.mkdir(parents=True, exist_ok=True)

    # Read and process file
    with open(input_file, 'r') as f:
        # Get content after last comment block if it exists
        content = f.read().split('- */\n')[-1]
        lines = content.splitlines()

    # Calculate positions and hashes
    positions = list(range(0, len(lines), interval))

    ends = []
    prefix_hashes = []
    hashes = []
    for pos in positions:
        # Join lines from position up to position+interval and compute hash
        r = min(len(lines), pos+interval)
        ends.append(r)
        prefix = '\n'.join(lines[:r])
        prefix_hashes.append(hash_content(prefix))

        segment = '\n'.join(lines[pos:r])
        hashes.append(hash_content(segment))

    # Write results
    with open(output_file, 'w') as f:
        f.write(f"hashes = {hashes}\n")
        f.write(f"prefix-hashes = {prefix_hashes}\n")
        f.write(f"positions = {ends}\n")

def main():
    # Configuration
    input_dir = Path("./lib")
    output_dir = Path("./hashes")
    interval = 8

    # Create output directory
    output_dir.mkdir(exist_ok=True)

    # Process all header files
    for input_file in input_dir.rglob("*"):
        # Skip directories
        if input_file.is_dir():
            continue

        # Calculate output path
        rel_path = input_file.relative_to(input_dir)
        output_file = output_dir / rel_path.with_name(rel_path.name + ".toml")

        process_header_file(input_file, output_file, interval)

if __name__ == "__main__":
    main()
