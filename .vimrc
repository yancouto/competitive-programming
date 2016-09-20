set ai si noet ts=4 sw=4 sta sm nu rnu
imap {<CR> {<CR>}<Esc>O
imap <C-up> <C-o>:m-2<CR>
imap <C-down> <C-o>:m+1<CR>
nmap <C-up> :m-2<CR>
nmap <C-down> :m+1<CR>
colors evening
" Non-essential
syntax on
set t_Co=8
highlight Normal ctermbg=NONE "No background
highlight nonText ctermbg=NONE
set list
set listchars=tab:▸\ ,trail:.
