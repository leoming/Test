retab<CR>
"set mouse=a
set nu
set sw=4
set ts=4
set et
set lbr
set fo+=mB
"set sm
set so=7
set wildmenu
set ruler
set wildignore=*.o,*~,*.pyc
set cmdheight=2
set backspace=eol,start,indent
set whichwrap+=<,>,h,l
set hid
set ignorecase
set smartcase
set hlsearch
set incsearch
set lazyredraw
set magic
set showmatch
set nobackup
set smartindent
"set mat=2
set noerrorbells
set novisualbell
set tm=500
filetype on
syntax enable
colorscheme desert
set background=dark
if has("gui_running")
    set guioptions-=T
    set guioptions+=e
endif
set encoding=utf8
set ffs=unix,dos,mac
set nowb
set noswapfile
set shiftwidth=4
set tw=500
set wrap
vnoremap <silent> * :call VisualSelection('f')<CR>
vnoremap <silent> # :call VisualSelection('b')<CR>
map s :w<cr>
map q :q!<cr>
map <space> /
"map <c-w>:w<CR>
"map <c-space> ?
"map <silent> <leader><cr> :noh<cr>
"map <C-j> <C-W>j
"map <C-k> <C-W>k
"map <C-h> <C-W>h
"map <C-l> <C-W>l
"map <leader>bd :Bclose<cr>
"map <leader>ba :1,1000 bd!<cr>
"map <leader>tn :tabnew<cr>
"map <leader>to :tabonly<cr>
"map <leader>tc :tabclose<cr>
"map <leader>tm :tabmove
"map <leader>te :tabedit <c-r>=expand("%:p:h")<cr>/
"map <leader>cd :cd %:p:h<cr>:pwd<cr>
try
  set switchbuf=useopen,usetab,newtab
  set stal=2
catch
endtry
autocmd BufReadPost *
     \ if line("'\"") > 0 && line("'\"") <= line("$") |
     \   exe "normal! g`\"" |
     \ endif
set viminfo^=%
"set laststatus=1
set statusline=\ %{HasPaste()}%F%m%r%h\ %w\ \ CWD:\ %r%{getcwd()}%h\ \ \ Line:\ %l
map 0 ^
nmap <M-j> mz:m+<cr>`z
nmap <M-k> mz:m-2<cr>`z
vmap <M-j> :m'>+<cr>`<my`>mzgv`yo`z
vmap <M-k> :m'<-2<cr>`>my`<mzgv`yo`z
if has("mac") || has("macunix")
  nmap <D-j> <M-j>
  nmap <D-k> <M-k>
  vmap <D-j> <M-j>
  vmap <D-k> <M-k>
endif
func! DeleteTrailingWS()
  exe "normal mz"
  %s/\s\+$//ge
  exe "normal `z"
endfunc
autocmd BufWrite *.py :call DeleteTrailingWS()
autocmd BufWrite *.coffee :call DeleteTrailingWS()
vnoremap <silent> gv :call VisualSelection('gv')<CR>
map <leader>g :vimgrep // **/*.<left><left><left><left><left><left><left>
map <leader><space> :vimgrep // <C-R>%<C-A><right><right><right><right><right><right><right><right><right>
vnoremap <silent> <leader>r :call VisualSelection('replace')<CR>
map <leader>cc :botright cope<cr>
map <leader>co ggVGy:tabnew<cr>:set syntax=qf<cr>pgg
map <leader>n :cn<cr>
map <leader>p :cp<cr>
"map <leader>ss :setlocal spell!<cr>
"map <leader>sn ]s
"map <leader>sp [s
"map <leader>sa zg
"map <leader>s? z=
noremap <Leader>m mmHmt:%s/<C-V><cr>//ge<cr>'tzt'm
map <leader>q :e ~/buffer<cr>
map <leader>pp :setlocal paste!<cr>
function! CmdLine(str)
    exe "menu Foo.Bar :" . a:str
    emenu Foo.Bar
    unmenu Foo
endfunction
function! VisualSelection(direction) range
    let l:saved_reg = @"
    execute "normal! vgvy"
    let l:pattern = escape(@", '\\/.*$^~[]')
    let l:pattern = substitute(l:pattern, "\n$", "", "")
    if a:direction == 'b'
        execute "normal ?" . l:pattern . "^M"
    elseif a:direction == 'gv'
        call CmdLine("vimgrep " . '/'. l:pattern . '/' . ' **/*.')
    elseif a:direction == 'replace'
        call CmdLine("%s" . '/'. l:pattern . '/')
    elseif a:direction == 'f'
        execute "normal /" . l:pattern . "^M"
    endif
    let @/ = l:pattern
    let @" = l:saved_reg
endfunction
function! HasPaste()
    if &paste
        return 'PASTE MODE  '
    en
    return ''
endfunction
command! Bclose call <SID>BufcloseCloseIt()
function! <SID>BufcloseCloseIt()
   let l:currentBufNum = bufnr("%")
   let l:alternateBufNum = bufnr("#")
   if buflisted(l:alternateBufNum)
     buffer #
   else
     bnext
   endif
   if bufnr("%") == l:currentBufNum
     new
   endif
   if buflisted(l:currentBufNum)
     execute("bdelete! ".l:currentBufNum)
   endif
endfunction
set cin
set cino=:0g0t0(sus
set cscopequickfix=s-,c-,d-,i-,t-,e-
"set autoindent
nmap <F3> :NERDTree <CR>
nmap <F2> :NERDTreeClose <CR>
let NERDChristmasTree=1
let NERDTreeAutoCenter=1
let NERDTreeBookmarksFile=$VIM.'\Data\NerdBookmarks.txt'
let NERDTreeMouseMode=2
let NERDTreeShowBookmarks=1
let NERDTreeShowFiles=1
let NERDTreeShowLineNumbers=1
let NERDTreeWinSize=24
nmap <F4> :Tlist <CR>
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1
let Tlist_Use_Right_Window=1
let Tlist_Use_SingleClick=0
let Tlist_Auto_Open=0
let Tlist_Process_File_Always=1
let Tlist_WinHeight=10
let Tlist_WinWidth=18
let Tlist_Use_Horiz_Window=0
set tags=tags;\
set autochdir
behave mswin
set ai
map <F5> :!ctags -R --c-kinds=+p --c++-kinds=+p --fields=+iaS --extra=+q . <CR>
map <F6> :WMToggle<CR> 
let g:winManagerWindowLayout="FileExplorer|BufExplorer|TagsExplorer"
let g:persistentBehaviour=0
let g:winManagerWidth=20
let g:defaultExplorer=2
set pastetoggle=<F7>
set nocompatible