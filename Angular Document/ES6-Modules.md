# ES6-Modules

https://hacks.mozilla.org/2015/08/es6-in-depth-modules/

## Module basics

An ES6 module is a file containing JS code. There’s no special `module` keyword; a module mostly reads just like a script. There are two differences.

- ES6 modules are automatically strict-mode code, even if you don’t write `"use strict";` in them.
- You can use `import` and `export` in modules.

```

export function detectCats(canvas, options) {
  var kittydar = new Kittydar(options);
  return kittydar.detectCats(canvas);
}

export class Kittydar {
  ... several methods doing image processing ...
}

// This helper function isn't exported.
function resizeCanvas() {
  ...
}
...
```

In a separate file, we can import and use the `detectCats()` function:

```
// demo.js - Kittydar demo program

import {detectCats} from "kittydar.js";

function go() {
    var canvas = document.getElementById("catpix");
    var cats = detectCats(canvas);
    drawRectangles(canvas, cats);
}
```

To import multiple names from a module, you would write:

```
import {detectCats, Kittydar} from "kittydar.js";
```

## Export lists

```
export {detectCats, Kittydar};

// no `export` keyword required here
function detectCats(canvas, options) { ... }
class Kittydar { ... }
```

An `export` list doesn’t have to be the first thing in the file; it can appear anywhere in a module file’s top-level scope. You can have multiple `export` lists, or mix `export` lists with other `export` declarations, as long as no name is exported more than once.

## Renaming imports and exports

ES6 lets you rename things when you import them:

```
import {flip as flipOmelet} from "eggs.js";
import {flip as flipHouse} from "real-estate.js";
```

Similarly, you can rename things when you export them. 

```
function v1() { ... }
function v2() { ... }

export {
  v1 as streamV1,
  v2 as streamV2,
  v2 as streamLatestVersion
};
```

## Default exports ???

The new standard is designed to interoperate with existing CommonJS  and AMD modules. So suppose you have a Node project and you’ve done `npm install lodash`. Your ES6 code can import individual functions from Lodash:

``

```
import {each, map} from "lodash";

each([3, 2, 1], x => console.log(x));
```

``

But perhaps you’ve gotten used to seeing `_.each` rather than `each` and you still want to write things that way. Or maybe you want to use `_` as a function, since [that’s a useful thing to do in Lodash](https://lodash.com/docs#_).

For that, you can use a slightly different syntax: import the module without curly braces.

``

```
import _ from "lodash";
```

``

This shorthand is equivalent to `import {default as _} from "lodash";`. All CommonJS and AMD modules are presented to ES6 as having a `default` export, which is the same thing that you would get if you asked `require()` for that module—that is, the `exports` object.

ES6 modules were designed to let you export multiple things, but for  existing CommonJS modules, the default export is all you get. For  example, as of this writing, the famous [colors](https://github.com/Marak/colors.js)  package doesn’t have any special ES6 support as far as I can tell. It’s  a collection of CommonJS modules, like most packages on npm. But you  can import it right into your ES6 code.

``

```
// ES6 equivalent of `var colors = require("colors/safe");`
import colors from "colors/safe";
```

``

If you’d like your own ES6 module to have a default export, that’s  easy to do. There’s nothing magic about a default export; it’s just like  any other export, except it’s named `"default"`. You can use the renaming syntax we already talked about:

``

```
let myObject = {
  field1: value1,
  field2: value2
};
export {myObject as default};
```

``

Or better yet, use this shorthand:

``

```
export default {
  field1: value1,
  field2: value2
};
```

``

The keywords `export default` can be followed by any value: a function, a class, an object literal, you name it.

## Module objects

```
import * as cows from "cows";
```

When you `import *`, what’s imported is a module namespace object. Its properties are the module’s exports. So if the “cows” module exports a function named `moo()`, then after importing “cows” this way, you can write: `cows.moo()`.

## Aggregating modules

Sometimes the main module of a package is little more than importing all the package’s other modules and exporting them in a unified way.

```
// world-foods.js - good stuff from all over

// import "sri-lanka" and re-export some of its exports
export {Tea, Cinnamon} from "sri-lanka";

// import "equatorial-guinea" and re-export some of its exports
export {Coffee, Cocoa} from "equatorial-guinea";

// import "singapore" and export ALL of its exports
export * from "singapore";
```

Unlike a real import, this doesn’t add the re-exported bindings to your scope. 

If any name exported by “singapore” happened to collide with the other exports, that would be an error, so use `export *` with care.

## what does import actually do?

ES6 leaves the details of module loading entirely [up to the implementation](http://www.ecma-international.org/ecma-262/6.0/index.html#sec-hostresolveimportedmodule). The rest of module execution is [specified in detail](http://www.ecma-international.org/ecma-262/6.0/index.html#sec-toplevelmoduleevaluationjob).

Roughly speaking, when you tell the JS engine to run a module, it has to behave as though these four steps are happening:

1. Parsing: The implementation reads the source code of the module and checks for syntax errors.

2. Loading: The implementation loads all imported modules (recursively). This is the part that isn’t standardized yet.

3. Linking: For each newly loaded module, the implementation creates a  module scope and fills it with all the bindings declared in that module,  including things imported from other modules.

   This is the part where if you try to `import {cake} from "paleo"`, but the “paleo” module doesn’t actually export anything named `cake`, you’ll get an error. And that’s too bad, because you were *so close* to actually running some JS code. And having cake!

4. Run time: Finally, the implementation runs the statements in the body of each newly-loaded module. By this time, `import` processing is already finished, so when execution reaches a line of code where there’s an `import` declaration… nothing happens!

But now we get to the fun part of this system. There’s a cool trick. 
Because the system doesn’t specify how loading works, and because you can figure out all the dependencies ahead of time by looking at the `import` declarations in the source code, an implementation of ES6 is free to do all the work at compile time and bundle all your modules into a single file to ship them over the network! And tools like [webpack](http://www.2ality.com/2015/04/webpack-es6.html) actually do this.

## Static vs. dynamic, or: rules and how to break them

For a dynamic language, JavaScript has gotten itself a surprisingly static module system.

- All flavors of `import` and `export` are allowed only at toplevel in a module. There are no conditional imports or exports, and you can’t use `import` in function scope.
- All exported identifiers must be explicitly exported by name in the  source code. You can’t programmatically loop through an array and export  a bunch of names in a data-driven way.
- Module objects are frozen. There is no way to hack a new feature into a module object, polyfill style.
- *All* of a module’s dependencies must be loaded, parsed, and linked eagerly, before any module code runs. There’s no syntax for an `import` that can be loaded lazily, on demand.
- There is no error recovery for `import` errors. An app may have hundreds of modules in it, and if anything fails to load or link, nothing runs. You can’t `import` in a `try/catch` block. (The upside here is that because the system is so static, webpack can detect those errors for you at compile time.)
- There is no hook allowing a module to run some code before its  dependencies load. This means that modules have no control over how  their dependencies are loaded.

That’s why whatever module-loading system you use will have a programmatic API to go alongside ES6’s static `import/export` syntax. For example, [webpack includes an API](http://webpack.github.io/docs/code-splitting.html)
that you can use for “code splitting”, loading some bundles of modules 
lazily on demand. The same API can help you break most of the other 
rules listed above.

## When can I use ES6 modules?

To use modules today, you’ll need a compiler such as [Traceur](https://github.com/google/traceur-compiler#what-is-traceur) or [Babel](http://babeljs.io/). Earlier in this series, [Gastón I. Silva showed how to use Babel and Broccoli](https://hacks.mozilla.org/2015/06/es6-in-depth-babel-and-broccoli/) to compile ES6 code for the web; building on that article, Gastón has [a working example with support for ES6 modules](https://github.com/givanse/broccoli-babel-examples/tree/master/es6-modules). This [post by Axel Rauschmayer](http://www.2ality.com/2015/04/webpack-es6.html) contains an example using Babel and webpack.