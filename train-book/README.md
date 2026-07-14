# Train Book

This directory captures *The American Railway* as a reusable source for the railroad-world project family.

The book is Dave's "train book": the recurring source text behind the railroad project ideas. These files preserve the raw OCR text, summarize the book's central technical themes, and provide cross-references into the design shelf.

## Files

- `raw/american-railway-1889-ocr.txt`: raw OCR text from the public-domain Internet Archive scan.
- `how-to-use.md`: short guide for using this directory while editing project designs or building automated analysis.
- `fingerprint.md`: compact structural and term-frequency fingerprint of the book.
- `themes.md`: central themes and interesting ideas to preserve in projects.
- `cross-reference.md`: links from book themes to Paper Railroad, Janney, and Tower.
- `project-design-support.md`: concrete design imports, vocabulary, diagnostics, and test ideas for the railroad projects.
- `topics/book-topics.yaml`: structured topic map for future automated analysis.

## Source

- Title: *The American Railway: Its Construction, Development, Management, and Appliances*
- Original publisher: Charles Scribner's Sons, 1889
- Internet Archive identifier: `americanrailwayi00coolrich`
- Internet Archive page: <https://archive.org/details/americanrailwayi00coolrich>

## Use

Use this directory as a book-derived lens when editing railroad designs.

The intended workflow is:

1. Start from a project idea in `../future-project-designs/`.
2. Check `cross-reference.md` for relevant book lenses.
3. Use `project-design-support.md` for concrete imports, diagnostics, and test ideas.
4. Use `themes.md` to preserve period texture and engineering concerns.
5. Use `topics/book-topics.yaml` as the source for future generated reports.
6. Promote only small executable details into project designs.

The book should guide vocabulary, constraints, diagnostics, and first principles. It should not force any project to model the entire railroad world at once.
