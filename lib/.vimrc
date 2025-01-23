/* -
name = "Vim"
[info]
- */
set cin aw ai is ts=4 sw=4 tm=50 nu noeb bg=dark ru cb=unnamedplus
sy on
ino jk <esc> | ino kj <esc>
ino { {<CR>}<Esc>ko
no ; :
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-6
