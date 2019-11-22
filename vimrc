" ----- Plugins
" Pathogen used for vim plugins
execute pathogen#infect()
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

" airline remove unicode symbols
if !exists('g:airline_symbols')
    let g:airline_symbols = {}
endif
let g:airline_left_alt_sep = ''
let g:airline_right_alt_sep = ''
let g:airline_symbols.crypt = ''
let g:airline_symbols.linenr = ''
let g:airline_symbols.maxlinenr = ' ln'
let g:airline_symbols.branch = ''
let g:airline_symbols.paste = 'ρ'
let g:airline_symbols.paste = 'Þ'
let g:airline_symbols.paste = '∥'
let g:airline_symbols.spell = 'Ꞩ'
let g:airline_symbols.notexists = 'Ɇ'
let g:airline_symbols.whitespace = 'Ξ'
let g:airline_symbols.branch = ''
let g:airline_symbols.readonly = ''
let g:airline_symbols.dirty=''

" gruvbox
colorscheme gruvbox
set background=dark    " Setting dark mode
let g:gruvbox_contrast_dark = 'hard'

let g:gruvbox_sign_column = 'bg0_h'

" ultisnips
let g:UltiSnipsExpandTrigger="<tab>"
let g:UltiSnipsJumpForwardTrigger="<tab>"

" ----- Basics
" replace delay when press escape
set ttimeoutlen=10

" Set numbers on left side
set number

filetype plugin indent on
set tabstop=8
set shiftwidth=4
set softtabstop=-1 " same value as shiftwidth
set expandtab
set smarttab
set autoindent
set incsearch

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

" Switch between buffers
nnoremap <C-z> :bp<CR>
nnoremap <C-x> :bn<CR>
nnoremap <C-c> :bp\|bd #<CR>
