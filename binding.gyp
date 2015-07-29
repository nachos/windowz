{
  "targets": [
    {
      "target_name": "windows",
      "sources": ["src/windows_win.cpp"],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
