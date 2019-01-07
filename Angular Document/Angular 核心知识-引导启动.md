# Angular 核心知识-引导启动

## 启动过程

NgModule 用于描述应用的各个部分如何组织在一起。每个应用有至少一个 Angular 模块，*根*模块就是你用来启动此应用的模块。按照惯例，它通常命名为 `AppModule`。

如果你使用 [Angular CLI](https://www.angular.cn/cli) 来生成一个应用，其默认的 `AppModule` 是这样的：

```
/* JavaScript imports */
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';

import { AppComponent } from './app.component';

/* the AppModule class with the @NgModule decorator */
@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
```

`@NgModule` 装饰器表明 `AppModule` 是一个 `NgModule` 类。 `@NgModule` 获取一个元数据对象，它会告诉 Angular 如何编译和启动本应用。

-  **declarations** —— 该应用所拥有的组件。
-  **imports** —— 导入 `BrowserModule` 以获取浏览器特有的服务，比如 DOM 渲染、无害化处理和位置（location）。
-  **providers** —— 各种服务提供商。
-    **bootstrap** —— *根*组件，Angular 创建它并插入 `index.html` 宿主页面。

CLI 创建的默认应用只有一个组件 `AppComponent`，所以它会同时出现在 `declarations` 和 `bootstrap` 数组中。

### declarations 数组

该模块的 `declarations` 数组告诉 Angular 哪些组件属于该模块。 当你创建更多组件时，也要把它们添加到 `declarations` 中。如果你使用了未声明过的组件，Angular 就会报错。

The `declarations` array only takes declarables. Declarables are components, [directives](https://www.angular.cn/guide/attribute-directives) and [pipes](https://www.angular.cn/guide/pipes). All of a module's declarables must be in the `declarations` array. Declarables must belong to exactly one module. The compiler emits an error if you try to declare the same class in more than one module.

这些可声明的类在当前模块中是可见的，但是对其它模块中的组件是不可见的 —— 除非把它们从当前模块导出，
并让对方模块导入本模块。

An example of what goes into a declarations array follows:

```
declarations: [
  YourComponent,
  YourPipe,
  YourDirective
],
```

**只有 @NgModule** 可以出现在 `imports` 数组中。

#### Using directives with `@NgModule`

To use a directive, component, or pipe in a module, you must do a few things:

1. Export it from the file where you wrote it.
2. Import it into the appropriate module.
3. Declare it in the `@NgModule` `declarations` array.

这三步的结果如下所示。在你创建指令的文件中导出它。下面的例子中，`item.directive.ts` 中的 `ItemDirective` 是 CLI 自动生成的默认指令结构。

```
// src/app/item.directive.ts
import { Directive } from '@angular/core';

@Directive({
  selector: '[appItem]'
})
export class ItemDirective {
// code goes here
  constructor() { }

}
```

The key point here is that you have to export it so you can import it elsewhere. Next, import it
into the NgModule, in this example `app.module.ts`, with a JavaScript import statement:

```
// src/app/app.module.ts
import { ItemDirective } from './item.directive';
```

And in the same file, add it to the `@NgModule` `declarations` array:

```
// src/app/app.module.ts
declarations: [
  AppComponent,
  ItemDirective
],
```

Now you could use your `ItemDirective` in a component. This example uses `AppModule`, but you'd do it the same way for a feature module. For more about directives, see [Attribute Directives](https://www.angular.cn/guide/attribute-directives) and [Structural Directives](https://www.angular.cn/guide/structural-directives). You'd also use the same technique for [pipes](https://www.angular.cn/guide/pipes) and components.

### imports 数组

模块的 `imports` 数组只会出现在 `@NgModule` 元数据对象中。它告诉 Angular 该模块想要正常工作，还需要哪些模块。

组件的模板中可以引用在当前模块中声明的或从其它模块中导入的组件、指令、管道。

### providers 数组

The providers array is where you list the services the app needs. When you list services here, they are available app-wide. You can scope them when using feature modules and lazy loading. For more information, see [Providers](https://www.angular.cn/guide/providers).

### bootstrap 数组

The application launches by bootstrapping the root `AppModule`, which is also referred to as an `entryComponent`. Among other things, the bootstrapping process creates the component(s) listed in the `bootstrap` array and inserts each one into the browser DOM.

每个被引导的组件都是它自己的组件树的根。插入一个被引导的组件通常触发一系列组件的创建并形成组件树。

虽然也可以在宿主页面中放多个组件，但是大多数应用只有一个组件树，并且只从一个根组件开始引导。

这个根组件通常叫做 `AppComponent`，并且位于根模块的 `bootstrap` 数组中。

### 关于 Angular 模块的更多知识

要进一步了解常见的 NgModules 知识，参见 [关于模块的常见问题](https://www.angular.cn/guide/frequent-ngmodules)。