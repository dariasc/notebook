#import "template.typ": *

#show: project.with()

#let extract_code(contents) = {
  return contents.split("- */\n").at(-1)
}
#let extract_metadata(contents) = {
  return toml.decode(contents.split("- */\n").at(0).split("/* -\n").at(-1))
}

#let insert(filename) = {
  let contents = read(filename)
  let metadata = extract_metadata(contents)
  return [
    #block[
      #v(0.75em)
      #block(breakable: false)[
        #heading(text(metadata.name, weight: "regular"))
        #block(
          for (key, value) in metadata.info {
            text(key + ": ", weight: "bold")
            eval(value, mode: "markup")
            linebreak()
          }
        )
      ]
      #raw(extract_code(contents), lang: "cpp", block: true)
      #line(length: 100%, stroke: 0.4pt)
    ]
  ]
}

#let section_title(title) = {
  return [
    = #text(title, size: 1.15em)
  ]
}

#block(width: 100%, height: 2.5em)[
  #align(bottom)[
    = #text("Team Notebook", size: 1.25em)
  ]
  #place(top + right)[
    #image("logo.svg", height: 3em)
  ]
]
#line(length: 100%, stroke: 0.4pt)
#v(-1em)

#insert("template.h")
#section_title("Data Structures")
#insert("ds/hashmap.h")
#insert("ds/order_statistic_tree.h")
#insert("ds/uf.h")
#insert("ds/convex_hull_trick.h")
#insert("ds/sparse_table.h")
#section_title("Strings")
#insert("strings/kmp.h")
#section_title("Graphs")
#insert("graph/topo_sort.h")
#insert("graph/dinic.h")
