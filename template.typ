#import "@preview/mitex:0.2.7": *

#let config = (
  columns: 3,
  gutter: 1.5%,
  margin-x: 0.6cm,
  margin-top: 1.25cm,
  margin-bottom: 0.9cm,
  header-ascent: 40%,

  code-size: 6.5pt,
  heading-above: 16pt,
  snippet-below: -6pt,
  snippet-gap: -8pt,
  hash-padding: 1.5pt,

  institution: "University of Chile",
  institution-short: "UCH",
  subtitle: "sin globito no hay fiesta",
  authors: "Diego Arias, Gabriel Carmona, Martín Ruiz-Tagle",
  logo: "logo.svg",
  logo-height: 128pt,
)

#let extract-code(contents) = {
  contents.split("- */\n").at(-1).trim("\n")
}

#let extract-metadata(contents) = {
  toml(bytes(contents.split("- */\n").at(0).split("/* -\n").at(-1)))
}

#let depends-unique(items) = {
  let deps = (:)
  for it in items {
    if "dependsOn" in it {
      for d in it.dependsOn {
        deps.insert(d, true)
      }
    }
  }
  deps
}

#let verified-files = depends-unique(json("stats.json"))

#let column-separators(cols: config.columns, margin: config.margin-x, gutter: config.gutter) = {
  let col-width = (100% - 2 * margin - (cols - 1) * gutter) / cols
  for i in range(1, cols) {
    let x = margin + i * col-width + (i - 0.5) * gutter
    place(
      top + left,
      line(start: (x, 5%), end: (x, 97%), stroke: 0.5pt + black),
    )
  }
}

#let notebook-header(institution: config.institution-short) = context {
  let headings = query(
    selector(heading.where(level: 2, outlined: true)).after(here()),
  )
  let this = headings.filter(it => it.location().position().page == here().position().page).map(it => it.body)
  grid(
    columns: (auto, 1fr, auto),
    text(institution, size: 9pt, weight: "semibold"),
    align(center, text(this.join(", "), size: 9pt, weight: "semibold")),
    text(counter(page).display("1"), size: 9pt, weight: "semibold"),
  )
}

#let notebook-cover(cfg: config) = {
  block(width: 100%, height: 100%, {
    set align(horizon + center)
    set par(spacing: 0em)
    if cfg.logo != none {
      image(cfg.logo, height: cfg.logo-height)
    }
    [
      #set text(size: 2.5em)
      #v(0.5em)
      *#cfg.institution*

      #v(1em)
      #cfg.subtitle
      #v(0.5em)

      #set text(size: 0.5em)
      #cfg.authors

      #set align(bottom + center)
      #datetime.today().display()
    ]
  })
}

#let snippet-header(metadata, is-verified: false) = {
  block(
    breakable: false,
    sticky: true,
    width: 100%,
    fill: gray.transparentize(80%),
    inset: 3pt,
    outset: (x: 3pt, y: 1.5pt),
  )[
    #set text(size: 8pt)
    #set par(leading: 0.5em)
    == #eval(metadata.at("name", default: ""), mode: "markup")
    #if is-verified [
      #set text(fill: olive.mix(lime), baseline: -2pt)
      #h(1fr)
      #sym.circle.filled
    ]
    #linebreak()
    #for (key, value) in metadata.at("info", default: (:)) {
      text(key + ": ", weight: "bold")
      eval(value, mode: "markup")
      linebreak()
    }
  ]
}

#let render-code-line(it, hash-metadata, line-count, padding: config.hash-padding) = {
  set box(width: 100%, outset: par.leading / 2)

  let body = if it.text == "" { " " } else { it.body }

  if hash-metadata != none and "positions" in hash-metadata and hash-metadata.positions.contains(it.number) {
    let index = hash-metadata.positions.position(i => i == it.number)
    let hash = hash-metadata.hashes.at(index)
    let prefix-hash = hash-metadata.prefix-hashes.at(index)
    let stroke = if it.number == line-count { 0.5pt + luma(25%) } else {
      (paint: gray.lighten(50%), thickness: 0.5pt, dash: "dashed")
    }

    box(inset: (bottom: padding))[
      #body
      #v(padding)
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

#let snippet-body(metadata, code, hash-metadata, line-count, hash-padding: config.hash-padding) = {
  show raw.line: it => render-code-line(it, hash-metadata, line-count, padding: hash-padding)

  let snippet-type = metadata.at("type", default: "cpp")
  if snippet-type == "typst" {
    set par(spacing: 0.5em)
    set text(size: 8pt)
    eval(code, mode: "markup")
  } else if snippet-type == "tex" {
    show heading.where(level: 2): it => [
      #v(0.5em)
      #it.body
    ]
    set par(spacing: 0.5em)
    set text(size: 8pt)
    set heading(outlined: false)
    mitext(code)
    set heading(outlined: true)
  } else {
    if code != "" {
      block(raw(code, lang: "cpp", block: true))
    }
  }
}

#let project(..args) = {
  let pos = args.pos()
  let body = pos.last()
  let user-cfg = if pos.len() > 1 { pos.first() } else { (:) } + args.named()
  let cfg = config + user-cfg

  set document(title: "Notebook")

  set page(
    paper: "a4",
    flipped: true,
    margin: (
      left: cfg.margin-x,
      right: cfg.margin-x,
      bottom: cfg.margin-bottom,
      top: cfg.margin-top,
    ),
    header-ascent: cfg.header-ascent,
    header: notebook-header(institution: cfg.institution-short),
  )

  set text(font: "New Computer Modern", lang: "en")
  set par(justify: true)

  show heading: set block(sticky: true)
  show heading.where(level: 1): it => {
    v(cfg.heading-above, weak: true)
    block(
      sticky: true,
      below: 0.8em,
      text(size: 1.1em, smallcaps(it.body)),
    )
  }
  show heading.where(level: 2): it => [
    #set text(weight: "regular")
    #it.body
  ]

  show outline.entry: it => link(
    it.element.location(),
    it.indented([], [#it.body() #h(1fr) #it.page()]),
  )

  show raw.where(block: true): it => {
    set text(cfg.code-size)
    set par(justify: false)
    it
  }
  set raw(theme: "theme.xml")

  notebook-cover(cfg: cfg)
  pagebreak()

  set page(
    background: column-separators(
      cols: cfg.columns,
      margin: cfg.margin-x,
      gutter: cfg.gutter,
    ),
  )
  show: std.columns.with(cfg.columns, gutter: cfg.gutter)
  body
}

#let index(depth: 1) = {
  outline(title: none, depth: depth)
}

#let insert(filename, ..args) = {
  let pos = args.pos()
  let user-cfg = if pos.len() > 0 { pos.first() } else { (:) } + args.named()
  let cfg = config + user-cfg

  let full-filename = "lib/" + filename
  let contents = read(full-filename)
  let hash-metadata = toml("hashes/" + filename + ".toml")
  let metadata = extract-metadata(contents)
  let code = extract-code(contents)
  let line-count = code.split("\n").len()
  let is-verified = full-filename in verified-files

  block[
    #if metadata.at("type", default: "cpp") == "tex" {
      v(1em)
    }

    #snippet-header(metadata, is-verified: is-verified)

    #v(cfg.snippet-gap)

    #snippet-body(
      metadata,
      code,
      hash-metadata,
      line-count,
      hash-padding: cfg.hash-padding,
    )

    #v(cfg.snippet-below)
  ]
}
