#let project(body) = {
  let vertical-line(anchor, x) = {
    place(
      top + anchor,
      line(
        start: (x, 5%),
        end: (x, 97%),
        stroke: 0.5pt + black
      ),
    )
  }

  set document(title: "Notebook")
  set page(
    paper: "a4",
    flipped: true,
    margin: ( left: 0.75cm, right: 0.75cm, bottom: 0.75cm, top: 1.25cm ),
    header-ascent: 40%,
    header: context {
      let headings = query(
        selector(heading.where(level: 2)).after(here())
      )
      let this = headings
        .filter((it) => it.location().position().page == here().position().page)
        .map((it) => it.body);
      return align(right, text(this.join(", "), size: 9pt, weight: "semibold"))
    },
    background: [
      #vertical-line(left, 34%)
      #vertical-line(right, -34%)
    ]
  )

  set text(font: "Libertinus Serif", lang: "en")
  set par(justify: true)
  show: columns.with(3, gutter: 2%)

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
    line(length: 100%, stroke: 0.5pt)
  }
}

#let extract-code(contents) = {
  return contents.split("- */\n").at(-1).trim("\n")
}

#let extract-metadata(contents) = {
  return toml.decode(contents.split("- */\n").at(0).split("/* -\n").at(-1))
}

#let hash-lines(text, end) = {
  bytes-to-hex(md5(
    text.split("\n")
      .slice(0, end)
      .join("")
      .replace(regex("\s+"), "")
    )
  ).slice(0, 6)
}

#let insert(filename) = {
  let contents = read("lib/" + filename)
  let hash-metadata = toml.decode(read("hashes/" + filename + ".toml"))
  let metadata = extract-metadata(contents)
  let code = extract-code(contents)
  let line-count = code.split("\n").len()
  return block[
    #block(breakable: false, width: 100%, fill: gray.transparentize(80%), inset: 3pt, outset: 3pt)[
      #set text(9pt)
      == #metadata.name
      #linebreak()
      #for (key, value) in metadata.info {
        text(key + ": ", weight: "bold")
        eval(value, mode: "markup")
        linebreak()
      }
    ]

    #show raw.line: it => {
      set box(
        width: 100%,
        outset: par.leading / 2,
      )

      let body = it.body
      if it.text == "" {
        body = " "
      }

      if hash-metadata.positions.contains(it.number) {
        let index = hash-metadata.positions.position(i => i == it.number)
        let hash = hash-metadata.hashes.at(index)
        let prefix-hash = hash-metadata.prefix-hashes.at(index)
        let stroke = (bottom: (paint: gray.lighten(50%), thickness: 0.5pt, dash: "dashed"))
        if it.number == line-count {
          stroke = (bottom: 0.5pt + black)
        }
        box(
          grid(
            columns: (1fr, 20pt),
            align: (auto, bottom + right),
            body,
            [
              #set text(size: 5pt)
              #hash,#text(prefix-hash, weight: "bold")
            ]
          ),
          stroke: stroke,
          inset: (bottom: 3pt),
          outset: (bottom: 1pt)
        )
      } else {
        box(body)
      }
    }
    #block(raw(code, lang: "cpp", block: true))
  ]
}
