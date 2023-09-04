#let project(title: "", authors: (), date: none, body) = {
  set document(author: authors, title: title)
  set page(paper: "us-letter", flipped: true, columns: 2, margin: 1cm, header-ascent: 20%, header: locate(loc => {
    let headings = query(
      selector(heading.where(level: 2)).after(loc),
      loc,
    )
    let this = headings
      .filter((it) => it.location().position().page == loc.position().page)
      .map((it) => it.body.child);

    return align(right + bottom, text(this.join(", "), size: 9pt, weight: "semibold"))
  }))
  set text(font: "Linux Libertine", lang: "en")
  set par(justify: true)

  show raw.where(block: true): it => {
    set text(8pt)
    set par(justify: false)
    it
  }
  set raw(theme: "theme.xml")

  body
}
