#let project(body) = {
  set document(title: "Notebook")
  set page(
    paper: "a4",
    flipped: true,
    margin: ( left: 1cm, right: 1cm, bottom: 1cm, top: 1.25cm ),
    header-ascent: 40%,
    header: locate(loc => {
      let headings = query(
        selector(heading.where(level: 2)).after(loc),
        loc,
      )
      let this = headings
        .filter((it) => it.location().position().page == loc.position().page)
        .map((it) => it.body);

      return align(right, text(this.join(", "), size: 9pt, weight: "semibold"))
    })
  )
  set text(font: "Linux Libertine", lang: "en")
  set par(justify: true)
  show: columns.with(3, gutter: 1%)

  show heading.where(level: 1): it => [
    #set block(above: 0em)
    #smallcaps[
      #it.body
    ]
  ]
  show heading.where(level: 2): it => [
    #set text(weight: "regular")
    #it.body
  ]

  show raw.where(block: true): it => {
    set text(7pt)
    set par(justify: false)
    it
  }
  set raw(theme: "theme.xml")

  body
}

#let title() = {
  return {
    block(width: 100%, height: 2.5em, {
      set text(size: 1.25em)
      align(bottom)[
        = Team Notebook
      ]
      place(top + right)[
        #image("logo.svg", height: 32pt)
      ]
    })
    line(length: 100%, stroke: 0.4pt)
  }
}

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
      #set text(9pt)
      #block(breakable: false)[
        == #metadata.name
        #linebreak()
        #for (key, value) in metadata.info {
          text(key + ": ", weight: "bold")
          eval(value, mode: "markup")
          linebreak()
        }
      ]
      #raw(extract_code(contents), lang: "cpp", block: true)
      #line(length: 100%, stroke: 0.4pt)
    ]
  ]
}
