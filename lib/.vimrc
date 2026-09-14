/* -
name = "Vim"
[info]
- */
set cin aw is et ts=2 sw=2 nu bg=dark cb=unnamedplus
sy on
ino {<CR> {<CR>}<Esc>ko
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-6
