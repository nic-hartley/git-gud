mergeInto(LibraryManager.library, [
  "print"
].reduce((p, c) => (p[c] = _=>{}) && p, {}));
