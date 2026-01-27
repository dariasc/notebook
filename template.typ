#import "@preview/digestify:0.1.0": *
#import "@preview/mitex:0.2.5": *
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
  let margin = 0.6cm
  let gutter = 1.5%
  set page(
    paper: "us-letter",
    flipped: true,
    margin: ( left: margin, right: margin, bottom: margin, top: 1.25cm ),
    header-ascent: 40%,
    header: context {
      let headings = query(
        selector(heading.where(level: 2)).after(here())
      )
      let this = headings
        .filter((it) => it.location().position().page == here().position().page)
        .map((it) => it.body);
      return [
        #grid(
          columns: (auto, 1fr, auto),
          text("UCH", size: 9pt, weight: "semibold"),
          align(center, text(this.join(", "), size: 9pt, weight: "semibold")),
          text(counter(page).display("1"), size: 9pt, weight: "semibold"),
        )
      ]
    },
  )

  set text(font: "New Computer Modern", lang: "en")
  set par(justify: true)

  show heading: set block(sticky: true)
  show heading.where(level: 1): it => [
    #set block(sticky: true, above: 1em)
    #set text(size: 1.1em)
    #block[
      #smallcaps[
        #it.body
      ]
    ]
  ]
  show heading.where(level: 2): it => [
    #set text(weight: "regular")
    #it.body
  ]
  show outline.entry: it => link(
    it.element.location(),
    it.indented([], [#it.body() #h(1fr) #it.page()]),
  )

  show raw.where(block: true): it => {
    set text(6.5pt)
    set par(justify: false)
    it
  }
  set raw(theme: "theme.xml")

  block(width: 100%, height: 100%, {
    set align(horizon + center)
    set par(spacing: 0em)
    image("logo.svg", height: 128pt)
    [
      #set text(size: 2.5em)
      #v(0.5em)
      *University of Chile*

      #v(1em)
      sin globito no hay fiesta 
      #v(0.5em)

      #set text(size: 0.5em)
      Diego Arias, Gabriel Carmona, Martín Ruiz-Tagle

      #set align(bottom + center)
      #datetime.today().display()
    ]
  })
  pagebreak()
  set page(
    background: [
      #vertical-line(left, margin + gutter/2 + (100% - 2*margin - 2*gutter) / 3)
      #vertical-line(right, -(margin + gutter/2 + (100% - 2*margin - 2*gutter) / 3))
    ]
  )
  show: columns.with(3, gutter: gutter)
  body
}

#let index() = {
  return outline(title: none, depth: 1)
}

#let insert(filename) = {
  let extract-code(contents) = {
    return contents.split("- */\n").at(-1).trim("\n")
  }

  let extract-metadata(contents) = {
    return toml(bytes(contents.split("- */\n").at(0).split("/* -\n").at(-1)))
  }

  let contents = read("lib/" + filename)
  let hash-metadata = toml("hashes/" + filename + ".toml")
  let metadata = extract-metadata(contents)
  let code = extract-code(contents)
  let line-count = code.split("\n").len()
  return block[
    #block(breakable: false, width: 100%, fill: gray.transparentize(80%), inset: 3pt, outset: 3pt)[
      #set text(8pt)
      == #eval(metadata.name, mode: "markup")
      #linebreak()
      #for (key, value) in metadata.info {
        text(key + ": ", weight: "bold")
        eval(value, mode: "markup")
        linebreak()
      }
    ]

    #v(-4pt)

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
        let stroke = (paint: gray.lighten(50%), thickness: 0.5pt, dash: "dashed")
        if it.number == line-count {
          stroke = 0.5pt + black
        }
        let divisor-padding = 1.5pt
        box(inset: (bottom: divisor-padding))[
          #body
          #v(divisor-padding)
          #place(bottom + left, dy: 2.5pt)[
            #line(stroke: stroke, length: 100% - 40pt)
          ]
          #place(bottom + right, dy: 4pt)[
            #rect(fill: white, inset: 0pt)[
              #set text(size: 5pt)
              #hash,#text(prefix-hash, weight: "bold")
            ]
          ]
        ]
      } else {
        body
      }
    }
    
    #if (metadata.at("type", default: "cpp") == "typst") {
      set par(spacing: 0.5em)
      set text(size: 8pt)
      eval(code, mode: "markup")
    } else if (metadata.at("type", default: "cpp") == "tex") {
      show heading.where(level: 2): it => [
        #v(1em)
        #it.body
      ]
      set par(spacing: 0.5em)
      set text(size: 8pt)
      mitext(code)
    } else {
      if code != "" {
        block(raw(code, lang: "cpp", block: true))
      }
    }

    #v(-4pt)
  ]
}

