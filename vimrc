" ----- Plugins
" Pathogen used for vim plugins
execute pathogen#infect()
" filetype plugin indent on
syntax on

autocmd FileType text,markdown let b:vcm_tab_complete = 'dict'

" CtrlP
set runtimepath^=~/afs/.confs/vim/bundle/ctrlp.vim
let g:ctrlp_custom_ignore = {
  \ 'dir':  '\v[\/](\.git|node_modules|dist|coverage|obj)$',
  \ 'file': '\v\.(o)$',
  \ }

" airline
let g:airline#extensions#branch#enabled = 1
let g:airline_section_y = 'BN: %{bufnr("%")}'
let g:airline_theme='wombat'

let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#formatter = 'unique_tail_improved'

let g:airline_left_sep = '▶'
let g:airline_right_sep = '◀'

" gruvbox
colorscheme gruvbox
set background=dark    " Setting dark mode
let g:gruvbox_contrast_dark = 'hard'

let g:gruvbox_sign_column = 'bg0_h'

" ----- Basics
" Set numbers on left side
set number

set expandtab
set autoindent
set tabstop=4
set incsearch
set hlsearch

set list listchars=tab:▸·,trail:·

" Highlight column 80
set colorcolumn=80

set laststatus=2
set splitright

" Multiscreen mapping
map <C-Left> <C-W><Left>
map <C-Right> <C-W><Right>
map <C-Up> <C-W><Up>
map <C-Down> <C-W><Down>

" Multitabs mapping
map <C-a> gt
