# windowz

Windowz is a tool to handle os windows

<table>
  <thead>
    <tr>
      <th>Linux</th>
      <th>OSX</th>
      <th>Windows</th>
      <th>Coverage</th>
      <th>Dependencies</th>
      <th>DevDependencies</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td colspan="2" align="center">
        <a href="https://travis-ci.org/nachos/windowz"><img src="https://img.shields.io/travis/nachos/windowz.svg?style=flat-square"></a>
      </td>
      <td align="center">
        <a href="https://ci.appveyor.com/project/nachos/windowz"><img src="https://img.shields.io/appveyor/ci/nachos/windowz.svg?style=flat-square"></a>
      </td>
      <td align="center">
<a href='https://coveralls.io/r/nachos/windowz'><img src='https://img.shields.io/coveralls/nachos/windowz.svg?style=flat-square' alt='Coverage Status' /></a>
      </td>
      <td align="center">
        <a href="https://david-dm.org/nachos/windowz"><img src="https://img.shields.io/david/nachos/windowz.svg?style=flat-square"></a>
      </td>
      <td align="center">
        <a href="https://david-dm.org/nachos/windowz#info=devDependencies"><img src="https://img.shields.io/david/dev/nachos/windowz.svg?style=flat-square"/></a>
      </td>
    </tr>
  </tbody>
</table>

## Have a problem? Come chat with us!
[![Join the chat at https://gitter.im/nachos/windowz](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/nachos/windowz?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## Installation
``` bash
  $ [sudo] npm install windowz --save
```

## Examples
### Initialize
``` js
var windowz = require('windowz');
```

### getAll
Get a list of all opened windows
``` js
var windows = windowz.getAll();
```

### getTitle(windowHandle)
Get the title of a window
``` js
var title = windowz.getTitle(windowHandle);
```

### setToForeground(windowHandle)
Set a window to foreground
``` js
windowz.setToForeground(windowHandle);
```
  
### minimize(windowHandle)
Minimize a given window
``` js
windowz.minimize(windowHandle);
```

### maximize(windowHandle)
Maximize a given window
``` js
windowz.maximize(windowHandle);
```

### activate(windowHandle)
Activate a given window
``` js
windowz.activate(windowHandle);
```

### show(windowHandle)
Show a given window
``` js
windowz.show(windowHandle);
```

### isForeground(windowHandle)
Returns if the window is the foreground window
``` js
var isForeground = windowz.isForeground(windowHandle);
```

### isMinimized(windowHandle)
Returns if the window is minimized
``` js
var isMinimized = windowz.isMinimized(windowHandle);
```

### setTopMost(windowHandle)
Sets the window to top most
``` js
windowz.setTopMost(windowHandle);
```

### setToForeground(windowHandle)
Sets the window to the foreground
``` js
windowz.setToForeground(windowHandle);
```

### close(windowHandle)
Closes the given window
``` js
windowz.close(windowHandle);
```
  
## Run Tests
``` bash
  $ npm test
```

## License

[MIT](LICENSE)
