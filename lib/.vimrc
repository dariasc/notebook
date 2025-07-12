/* -
name = "Vim"
[info]
- */
set cin aw ai is ts=4 sw=4 nu noeb bg=dark ru cb=unnamedplus
sy on
ino jk <esc> | ino kj <esc>
ino {<CR> {<CR>}<Esc>ko
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-6
