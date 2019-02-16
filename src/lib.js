// The functions that we expect the JavaScript side to provide
let e = [
  'draw_commit_circle', 'connect_circles', 'print'
]

// tell Emscripten to make room for those:
mergeInto(LibraryManager.library,e.reduce((p,c)=>(p[c]=_=>{},p),{}));
