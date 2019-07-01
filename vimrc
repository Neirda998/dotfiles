" Pathogen used for vim plugins
execute pathogen#infect()

" Set numbers on left side
set number

" Spell checking
set spell spelllang=en_gb

set expandtab
set tabstop=2
set incsearch
set hlsearch

" Highlight column 80
set colorcolumn=80
highlight ColorColumn ctermbg=0

autocmd FileType text,markdown let b:vcm_tab_complete = 'dict'

set laststatus=2
set splitright

" CtrlP ignore
let g:ctrlp_custom_ignore = {
  \ 'dir':  '\v[\/](\.git|node_modules|dist|coverage|obj)$',
  \ 'file': '\v\.(o)$',
  \ }

" Multiscreen mapping
map <C-Left> <C-W><Left>
map <C-Right> <C-W><Right>
map <C-Up> <C-W><Up>
map <C-Down> <C-W><Down>

" Tabs mapping
map <C-a> gt
