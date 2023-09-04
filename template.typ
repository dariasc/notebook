#let project(title: "", authors: (), date: none, body) = {
  set document(author: authors, title: title)
  set page(paper: "us-letter", flipped: true, columns: 2, margin: 1cm, background: [
    #line(
        length: 94%, 
        angle: 90deg, 
        stroke: 0.0pt
    )
  ])
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
