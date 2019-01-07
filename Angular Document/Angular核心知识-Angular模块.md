# Angular 核心知识-Angular 模块

## NgModule 简介

### Angular 模块(NgModule)

**NgModules** configure the injector and the compiler and help organize related things together.

An NgModule is a class marked by the `@NgModule` decorator. `@NgModule` takes a metadata object that describes how to compile a component's template and how to create an injector at runtime. It identifies the module's own components, directives, and pipes, making some of them public, through the `exports` property, so that external components can use them. `@NgModule` can also add service providers to the application dependency injectors.

### Angular 模块化

Modules are a great way to organize an application and extend it with capabilities from external libraries.

Angular libraries are NgModules, Many third-party libraries are available as NgModules.

NgModules consolidate components, directives, and pipes into cohesive blocks of functionality, each focused on a feature area, application business domain, workflow, or common collection of utilities.

Modules can also add services to the application. Such services might be internally developed, like something you'd develop yourself or come from outside sources, such as the Angular router and HTTP client.

模块可以在应用启动时立即加载，也可以由路由器进行异步的惰性加载。

NgModule metadata does the following:

-  Declares which components, directives, and pipes belong to the module.
-  Makes some of those components, directives, and pipes public so that other module's component templates can use them.
-  Imports other modules with the components, directives, and pipes that components in the current module need.
-  Provides services that the other application components can use.

Every Angular app has at least one module, the root module. You [bootstrap](https://www.angular.cn/guide/bootstrapping) that module to launch the application.

对于那些只有少量组件的简单应用，根模块就是你所需的一切。随着应用的成长，你要把这个根模块重构成一些[特性模块](https://www.angular.cn/guide/feature-modules)，它们代表一组密切相关的功能集。然后你再把这些模块导入到根模块中。

### 关于 NgModule 的更多知识

你可能还对下列内容感兴趣：

-  [特性模块](https://www.angular.cn/guide/feature-modules)
-  [入口组件](https://www.angular.cn/guide/entry-components)
-  [服务提供商](https://www.angular.cn/guide/providers)。
-  [NgModule 的分类](https://www.angular.cn/guide/module-types).

## JS 模块 vs NgModule

JavaScript 和 Angular 都使用模块来组织代码，虽然它们的组织形式不同，但 Angular 的应用会同时依赖两者。

### JavaScript 模块

在 JavaScript 中，模块是内含 JavaScript 代码的独立文件。要让其中的东西可用，你要写一个导出语句，通常会放在相应的代码之后，类似这样：

```
export class AppComponent { ... }
```

然后，当你在其它文件中需要这个文件的代码时，要像这样导入它：

```
import { AppComponent } from './app.component';
```

JavaScript 模块让你能为代码加上命名空间，防止因为全局变量而引起意外。

### NgModules

NgModule 是一些带有 `@NgModule` 装饰器的类。`@NgModule` 装饰器的 `imports` 数组会告诉 Angular 哪些其它的 NgModule 是当前模块所需的。`imports` 数组中的这些模块与 JavaScript 模块不同，它们都是 NgModule 而不是常规的 JavaScript 模块。带有 `@NgModule` 装饰器的类通常会习惯性地放在单独的文件中, but what makes them an `NgModule` isn’t being in their own file, like JavaScript modules; it’s the presence of `@NgModule` and its metadata.

The `AppModule` generated from the [Angular CLI](https://www.angular.cn/cli) demonstrates both kinds of modules in action:

```
/* These are JavaScript import statements. Angular doesn’t know anything about these. */
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';

/* The @NgModule decorator lets Angular know that this is an NgModule. */
@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [     /* These are NgModule imports. */
    BrowserModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
```

The NgModule classes differ from JavaScript module in the following key ways:

- An NgModule bounds [declarable classes](https://www.angular.cn/guide/ngmodule-faq#q-declarable) only.Declarables are the only classes that matter to the [Angular compiler](https://www.angular.cn/guide/ngmodule-faq#q-angular-compiler).
- Instead of defining all member classes in one giant file as in a JavaScript module, you list the module's classes in the `@NgModule.declarations` list.
- An NgModule can only export the [declarable classes](https://www.angular.cn/guide/ngmodule-faq#q-declarable) it owns or imports from other modules. It doesn't declare or export any other kind of class.
- Unlike JavaScript modules, an NgModule can extend the *entire* application with services
  by adding providers to the `@NgModule.providers` list.

### 关于 NgModule 的更多知识

要了解关于 NgModule 的更多知识，参见

-  [引导启动](https://www.angular.cn/guide/bootstrapping)。
-  [常用模块](https://www.angular.cn/guide/frequent-ngmodules)。
-  [服务提供商](https://www.angular.cn/guide/providers)。

## 常用模块

### 常用模块

Angular 应用需要不止一个模块，它们都为根模块服务。如果你要把某些特性添加到应用中，可以通过添加模块来实现。下列是一些常用的 Angular 模块，其中带有一些其内容物的例子：

| NgModule              | 导入自                      | 为何使用                                                     |
| --------------------- | --------------------------- | ------------------------------------------------------------ |
| `BrowserModule`       | `@angular/platform-browser` | 当你想要在浏览器中运行应用时                                 |
| `CommonModule`        | `@angular/common`           | 当你想要使用 `NgIf` 和 `NgFor` 时                            |
| `FormsModule`         | `@angular/forms`            | When you want to build template driven forms (includes `NgModel`) |
| `ReactiveFormsModule` | `@angular/forms`            | 当要构建响应式表单时                                         |
| `RouterModule`        | `@angular/router`           | When you want to use `RouterLink`,`.forRoot()`, and `.forChild()` |
| `HttpClientModule`    | `@angular/common/http`      | 当你要和服务器对话时                                         |

### 导入模块

When you use these Angular modules, import them in `AppModule`, or your feature module as appropriate, and list them in the `@NgModule` `imports` array. For example, in the basic app generated by the [Angular CLI](https://www.angular.cn/cli), `BrowserModule` is the first import at the top of the `AppModule`, `app.module.ts`.

###  `BrowserModule` 和 `CommonModule`

`BrowserModule` 导入了 `CommonModule`，它贡献了很多通用的指令，比如 `ngIf` 和 `ngFor`。 另外，`BrowserModule` 重新导出了 `CommonModule`，以便它所有的指令在任何导入了 `BrowserModule` 的 Angular 模块中都可以使用。

对于运行在浏览器中的应用来说，都必须在根模块中 `AppModule` 导入 `BrowserModule` ，因为它提供了启动和运行浏览器应用时某些必须的服务。`BrowserModule` 的提供商是面向整个应用的，所以它只能在根模块中使用，而不是特性模块。 特性模块只需要 `CommonModule` 中的常用指令，它们不需要重新安装所有全应用级的服务。

如果你把 `BrowserModule` 导入了惰性加载的特性模块中，Angular 就会返回一个错误，并告诉你应该改用 `CommonModule`。

![BrowserModule error](https://www.angular.cn/generated/images/guide/frequent-ngmodules/browser-module-error.gif)

## 特性模块的分类

There are five general categories of feature modules which tend to fall into the following groups:

- Domain feature modules.
- Routed feature modules.
- Routing modules.
- Service feature modules.
- Widget feature modules.

While the following guidelines describe the use of each type and their typical characteristics, in real world apps, you may see hybrids.

| 特性模块 | 指导原则                                                     |
| -------- | ------------------------------------------------------------ |
| Domain   | 领域特性模块用来给用户提供应用程序领域中特有的用户体验，比如编辑客户信息或下订单等。       They typically have a top component that acts as the feature root and private, supporting sub-components descend from it.       领域特性模块大部分由 `declarations` 组成，只有顶级组件会被导出。       领域特性模块很少会有服务提供商。如果有，那么这些服务的生命周期必须和该模块的生命周期完全相同。       Domain feature modules are typically imported exactly once by a larger feature module.       对于缺少路由的小型应用，它们可能只会被根模块 `AppModule` 导入一次。 |
| Routed   | Routed feature modules are domain feature modules whose top components are the targets of router navigation routes.       根据这个定义，所有惰性加载的模块都是路由特性模块。       带路由的特性模块不会导出任何东西，因为它们的组件永远不会出现在外部组件的模板中。       A lazy-loaded routed feature module should not be imported by any <br/>module. Doing so would trigger an eager load, defeating the purpose of 
lazy loading.That means you won’t see them mentioned among the `AppModule`
imports. An eager loaded routed feature module must be imported by 
another module so that the compiler learns about its components.       路由特性模块很少会有服务提供商，原因参见[惰性加载的特性模块](https://www.angular.cn/guide/lazy-loading-ngmodules)中的解释。如果那样做，那么它所提供的服务的生命周期必须与该模块的生命周期完全相同。不要在路由特性模块或被路由特性模块所导入的模块中提供全应用级的单例服务。 |
| Routing  | 路由模块为其它模块提供路由配置，并且把路由这个关注点从它的配套模块中分离出来。       路由模块通常会做这些：                       定义路由。                       把路由配置添加到该模块的 `imports` 中。                       把路由守卫和解析器的服务提供商添加到该模块的 `providers` 中。                       路由模块应该与其配套模块同名，但是加上“Routing”后缀。比如，`foo.module.ts` 中的 `FooModule` 就有一个位于 `foo-routing.module.ts` 文件中的 `FooRoutingModule` 路由模块。 如果其配套模块是根模块 `AppModule`，`AppRoutingModule` 就要使用 `RouterModule.forRoot(routes)` 来把路由器配置添加到它的 `imports` 中。 所有其它路由模块都是子模块，要使用 `RouterModule.forChild(routes)`。                       按照惯例，路由模块会重新导出这个 `RouterModule`，以便其配套模块中的组件可以访问路由器指令，比如 `RouterLink` 和 `RouterOutlet`。                       A routing module does not have its own declarations. 组件、指令和管道都是特性模块的职责，而不是路由模块的。                   路由模块只应该被它的配套模块导入。 |
| 服务     | 服务模块提供了一些工具服务，比如数据访问和消息。理论上，它们应该是完全由服务提供商组成的，不应该有可声明对象。Angular 的 `HttpClientModule` 就是一个服务模块的好例子。       根模块 `AppModule` 是唯一的可以导入服务模块的模块。 |
| 窗口部件 | 窗口部件模块为外部模块提供组件、指令和管道。很多第三方 UI 组件库都是窗口部件模块。       窗口部件模块应该完全由可声明对象组成，它们中的大部分都应该被导出。       窗口部件模块很少会有服务提供商。       如果任何模块的组件模板中需要用到这些窗口部件，就请导入相应的窗口部件模块。 |

下表中汇总了各种特性模块类型的关键特征。

| 特性模块 | 声明 `declarations` | 提供商 `providers` | 导出什么     | 被谁导入            |
| -------- | ------------------- | ------------------ | ------------ | ------------------- |
| 领域     | 有                  | 罕见               | 顶级组件     | 特性模块，AppModule |
| 路由     | 有                  | 罕见               | 无           | 无                  |
| 路由     | 无                  | 是（守卫）         | RouterModule | 特性（供路由使用）  |
| 服务     | 无                  | 有                 | 无           | AppModule           |
| 窗口部件 | 有                  | 罕见               | 有           | 特性                |

## 入口组件

An entry component is any component that Angular loads imperatively, (which means you’re not referencing it in the template), by type. You specify an entry component by bootstrapping it in an NgModule, or including it in a routing definition.

### 引导用的入口组件

下面这个例子中指定了一个引导用组件 `AppComponent`，位于基本的 `app.module.ts` 中：

```
@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpClientModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent] // bootstrapped entry component
})
```

可引导组件是一个入口组件，Angular 会在引导过程中把它加载到 DOM 中。 其它入口组件是在其它时机动态加载的，比如用路由器。

Angular 会动态加载根组件 `AppComponent`，是因为它的类型作为参数传给了 `@NgModule.bootstrap` 函数。

> 组件也可以在该模块的 `ngDoBootstrap()` 方法中进行命令式引导。`@NgModule.bootstrap` 属性告诉编译器，这里是一个入口组件，它应该生成代码，来使用这个组件引导该应用。

A bootstrapped component is necessarily an entry component because bootstrapping is an imperative process, thus it needs to have an entry component.  ???

###  路由到的入口组件

入口组件的第二种类型出现在路由定义中，就像这样：

```
const routes: Routes = [
  {
    path: '',
    component: CustomerListComponent
  }
];
```

路由定义使用组件类型引用了一个组件：`component: CustomerListComponent`。

所有路由组件都必须是入口组件。这需要你把同一个组件添加到两个地方（路由中和 `entryComponents` 中），但编译器足够聪明，可以识别出这里是一个路由定义，因此它会自动把这些路由组件添加到 `entryComponents` 中。

### entryComponents 数组

虽然 `@NgModule` 装饰器具有一个 `entryComponents` 数组，但大多数情况下你不用显式设置入口组件，因为 Angular 会自动把 `@NgModule.bootstrap` 中的组件以及路由定义中的组件添加到入口组件中。Though these two mechanisms account for most entry components, if your app happens to bootstrap or dynamically load a component by type imperatively, you must add it to `entryComponents` explicitly.

#### entryComponents 和编译器

对于生产环境的应用，你总是希望加载尽可能小的代码。这些代码应该只包含你实际使用到的类，并且排除那些从未用到的组件。因此，Angular 编译器只会为那些可以从 `entryComponents` 中直接或间接访问到的组件生成代码。这意味着，仅仅往 `@NgModule.declarations` 中添加更多引用，并不能表达出它们在最终的代码包中是必要的。

In fact, many libraries declare and export components you'll never use. For example, a material design library will export all components because it doesn’t know which ones you will use. However, it is unlikely that you will use them all. For the ones you don't reference, the tree shaker drops these components
from the final code package.

如果一个组件既不是**入口组件**也没有在模板中使用过，摇树优化工具就会把它扔出去。所以，最好只添加那些真正的入口组件，以便让应用尽可能保持精简。

## 特性模块

特性模块是用来对代码进行组织的模块。

### 特性模块 vs. 根模块

与核心的 Angular API 的概念相反，特性模块是最佳的组织方式。特性模块提供了聚焦于特定应用需求的一组功能，比如用户工作流、路由或表单。虽然你也可以用根模块做完所有事情，不过特性模块可以帮助你把应用划分成一些聚焦的功能区。特性模块通过它提供的服务以及共享出的组件、指令和管道来与根模块和其它模块合作。

### 如何制作特性模块

如果你已经有了 [Angular CLI](https://www.angular.cn/cli) 生成的应用，可以在项目的根目录下输入下面的命令来创建特性模块。把这里的 `CustomerDashboard` 替换成你的模块名。你可以从名字中省略掉“Module”后缀，因为 CLI 会自动追加上它：

```
ng generate module CustomerDashboard
```

这会让 CLI 创建一个名叫 `customer-dashboard` 的文件夹，其中有一个名叫 `customer-dashboard.module.ts`，内容如下：

```
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

@NgModule({
  imports: [
    CommonModule
  ],
  declarations: []
})
export class CustomerDashboardModule { }
```

`BrowserModule`只应该在根模块中导入一次。`CommonModule` 只包含常用指令的信息，比如 `ngIf` 和 `ngFor`，它们在大多数模板中都要用到，而 `BrowserModule` 为浏览器所做的应用配置只会使用一次。

`declarations` 数组让你能添加专属于这个模块的可声明对象（组件、指令和管道）。要添加组件，就在命令行中输入如下命令，这里的 `customer-dashboard` 是一个目录，CLI 会把特性模块生成在这里，而 `CustomerDashboard` 就是该组件的名字：

```
ng generate component customer-dashboard/CustomerDashboard
```

这会在 `customer-dashboard` 中为新组件生成一个目录，并使用 `CustomerDashboardComponent` 的信息修改这个特性模块：

```
// import the new component
import { CustomerDashboardComponent } from './customer-dashboard/customer-dashboard.component';
@NgModule({
  imports: [
    CommonModule
  ],
  declarations: [
    CustomerDashboardComponent
  ],
})
```

### 导入特性模块

要想把这个特性模块包含进应用中，你还得让根模块 `app.module.ts` 知道它。注意，在 `customer-dashboard.module.ts` 的底部导出了 `CustomerDashboardModule`。这样就把它暴露出来，以便其它模块可以拿到它。要想把它导入到 `AppModule` 中，就把它加入 `app.module.ts` 的导入表中，并将其加入 `imports` 数组：

```
// src/app/app.module.ts
import { HttpClientModule } from '@angular/common/http';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
// import the feature module here so you can add it to the imports array below
import { CustomerDashboardModule } from './customer-dashboard/customer-dashboard.module';

@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpClientModule,
    CustomerDashboardModule // add the feature module here
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
```

现在 `AppModule` 知道这个特性模块了。如果你往该特性模块中加入过任何服务提供商，`AppModule` 也同样会知道它，其它模块中也一样。不过，NgModule 并不会暴露出它们的组件。

### 渲染特性模块的组件模板

当 CLI 为这个特性模块生成 `CustomerDashboardComponent` 时，还包含一个模板 `customer-dashboard.component.html`，它带有如下页面脚本：

```
// src/app/customer-dashboard/customer-dashboard/customer-dashboard.component.html
<p>
  customer-dashboard works!
</p>
```

要想在 `AppComponent` 中查看这些 HTML，你首先要在 `CustomerDashboardModule` 中导出 `CustomerDashboardComponent`。在 `customer-dashboard.module.ts` 中，`declarations` 数组的紧下方，加入一个包含 `CustomerDashboardModule` 的 `exports` 数组：

```
// src/app/customer-dashboard/customer-dashboard.module.ts
exports: [
  CustomerDashboardComponent
]
```

然后，在 `AppComponent` 的 `app.component.html` 中，加入标签 `<app-customer-dashboard>`：

```
// src/app/app.component.html
<h1>
  {{title}}
</h1>

<!-- add the selector from the CustomerDashboardComponent -->
<app-customer-dashboard></app-customer-dashboard>
```

## 服务提供商

A provider is an instruction to the DI system on how to obtain a value for a dependency. Most of the time, these dependencies are services that you create and provide.

### 提供服务

如果你是用 [Angular CLI](https://www.angular.cn/cli) 创建的应用，那么可以使用下列 CLI 的 [`ng generate`](https://www.angular.cn/cli/generate) 命令在项目根目录下创建一个服务。把其中的 `User` 替换成你的服务名。

```
ng generate service User
```

该命令会创建下列 `UserService` 骨架：

```
// src/app/user.service.0.ts
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class UserService {
}
```

现在，你就可以在应用中到处注入 `UserService` 了。该服务本身是 CLI 创建的一个类，并且加上了 `@Injectable` 装饰器。默认情况下，该装饰器是用 `providedIn` 属性进行配置的，它会为该服务创建一个提供商。在这个例子中，`providedIn: 'root'` 指定该服务应该在根注入器中提供。

### 提供商的作用域

当你把服务提供商添加到应用的根注入器中时，它就在整个应用程序中可用了。另外，这些服务提供商也同样对整个应用中的类是可用的 —— 只要它们有供查找用的服务令牌。

You should always provide your service in the root injector unless there is a case where you want the service to be available only if the consumer imports a particular `@NgModule`.

### providedIn 与 NgModule

也可以规定某个服务只有在特定的 `@NgModule` 中提供。比如，如果你你希望只有当消费方导入了你创建的 `UserModule` 时才让 `UserService` 在应用中生效，那就可以指定该服务要在该模块中提供：

```
// src/app/user.service.1.ts
import { Injectable } from '@angular/core';
import { UserModule } from './user.module';

@Injectable({
  providedIn: UserModule,
})
export class UserService {
}
```

上面的例子展示的就是在模块中提供服务的首选方式。之所以推荐该方式，是因为当没有人注入它时，该服务就可以被摇树优化掉。 If it's not possible to specify in the service which module should provide it, you can also declare a provider for the service within the module:

```
// src/app/user.module.ts
import { NgModule } from '@angular/core';

import { UserService } from './user.service';

@NgModule({
  providers: [UserService],
})
export class UserModule {
}
```

### 使用惰性加载模块限制提供商的作用域

在 CLI 生成的基本应用中，模块是立即加载的，这意味着它们都是由本应用启动的，Angular 会使用一个依赖注入体系来让一切服务都在模块间有效。对于立即加载式应用，应用中的根注入器会让所有服务提供商都对整个应用有效。

当使用惰性加载时，这种行为需要进行改变。惰性加载就是只有当需要时才加载模块，比如路由中。它们没办法像立即加载模块那样进行加载。这意味着，在它们的 `providers` 数组中列出的服务都是不可用的，因为根注入器并不知道这些模块

When the Angular router lazy-loads a module, it creates a new injector. This injector is a child of the root application injector. Imagine a tree of injectors; there is a single root injector and then a child injector for each lazy loaded module. The router adds all of the providers from the root injector to the child injector. When the router creates a component within the lazy-loaded context, Angular prefers service instances created from these providers to the service instances of the application root injector.

Any component created within a lazy loaded module’s context, such as by router navigation, gets the local instance of the service, not the instance in the root application injector. Components in external modules continue to receive the instance created for the application root.

Though you can provide services by lazy loading modules, not all services can be lazy loaded. For instance, some modules only work in the root module, such as the Router. The Router works with the global location object in the browser.

### 使用组件限定服务提供商的作用域

Another way to limit provider scope is by adding the service you want to limit to the component’s
`providers` array. Component providers and NgModule providers are independent of each other. This
method is helpful for when you want to eagerly load a module that needs a service all to itself.
Providing a service in the component limits the service only to that component (other components in
the same module can’t access it.)

```
// src/app/app.component.ts
@Component({
/* . . . */
  providers: [UserService]
})
```

### 在模块中提供服务还是在组件中？

Generally, provide services the whole app needs in the root module and scope services by providing them in lazy loaded modules.

路由器工作在根级，所以如果你把服务提供商放进组件（即使是 `AppComponent`）中，那些依赖于路由器的惰性加载模块，将无法看到它们。

Register a provider with a component when you must limit a service instance to a component and its component tree, that is, its child components. For example, a user editing component, `UserEditorComponent`, that needs a private copy of a caching `UserService` should register the `UserService` with the `UserEditorComponent`. Then each new instance of the `UserEditorComponent` gets its own cached service instance.

## 单例服务

### 提供单例服务

在 Angular 中有两种方式来生成单例服务：

- 声明该服务应该在应用的根上提供。
- 把该服务包含在 `AppModule` 或某个只会被 `AppModule` 导入的模块中。

从 Angular 6.0 开始，创建单例服务的首选方式是在那个服务类上指定它应该在应用的根上提供。只要在该服务的 `@Injectable` 装饰器上把 `providedIn` 设置为 `root` 就可以了：

```
// src/app/user.service.0.ts
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class UserService {
}
```

### forRoot()

如果某个模块同时提供了服务提供商和可声明对象（组件、指令、管道），那么当在某个子注入器中加载它的时候（比如路由），就会生成多个该服务提供商的实例。而存在多个实例会导致一些问题，因为这些实例会屏蔽掉根注入器中该服务提供商的实例，而它的本意可能是作为单例对象使用的。For this reason Angular provides a way to separate providers out of the module so that same module can be imported into the root module with `providers` and child modules without `providers`.

1. 在该模块上创建一个静态方法 `forRoot()`（习惯名称）。
2. 把那些服务提供商放进 `forRoot` 方法中，参见下面的例子。

以 `RouterModule` 为例具体说说。`RouterModule` 要提供 `Router` 服务，还要提供 `RouterOutlet` 指令。
`RouterModule` 要由根应用模块导入，以便该应用拥有一个路由器，而且它还需要至少一个 `RouterOutlet`。
`RouterModule` 还必须由各个独立的路由组件导入，让它们能在自己的模板中使用 `RouterOutlet` 指令来支持其子路由。???

如果 `RouterModule` 没有 `forRoot()`，那么每个路由组件都会创建一个新的 `Router` 实例。这将会破坏整个应用，因为应用中只能有一个 `Router`。`RouterModule` 拥有 `RouterOutlet` 指令，它应该随处可用，但是 `Router` 只能有一个，它应该在 `forRoot()` 中提供。最终的结果就是，应用的根模块导入`RouterModule.forRoot(...)` 以获取 `Router`，而所有路由组件都导入了 `RouterModule`，它不包括这个 `Router` 服务。

如果你有一个同时提供服务提供商和可声明对象的模块，请使用下面的模式把它们分离开。

那些需要把服务提供商加到应用中的模块可以通过某种类似 `forRoot()` 方法的方式配置那些服务提供商。

`forRoot()` 接收一个服务配置对象，然后返回一个 [ModuleWithProviders](https://www.angular.cn/api/core/ModuleWithProviders) ，它是一个带有下列属性的简单对象：

-  `ngModule`： 在这个例子中就是 `CoreModule` 类
-  `providers` - 配置好的服务提供商

在这个[在线例子](https://www.angular.cn/generated/live-examples/ngmodules/stackblitz.html) / [下载范例](https://www.angular.cn/generated/zips/ngmodules/ngmodules.zip)中，根 `AppModule` 导入了 `CoreModule`，并把它的 `providers` 添加到了 `AppModule` 的服务提供商中。特别是，Angular 会在 `@NgModule.providers` 前面添加这些导入的服务提供商。这种顺序保证了 `AppModule` 中的服务提供商总是会优先于那些从其它模块中导入的服务提供商。

应该只在 `AppModule` 中导入 `CoreModule` 并只使用一次 `forRoot()` 方法，因为该方法中会注册服务，而你希望那些服务在该应用中只注册一次。如果你多次注册它们，就可能会得到该服务的多个实例，并导致运行时错误。

你还可以在 `CoreModule` 中添加一个用于配置 `UserService` 的 `forRoot()` 方法。

在下面的例子中，可选的注入 `UserServiceConfig` 扩展了 `Core` 模块中的 `UserService`。如果 `UserServiceConfig` 存在，就从这个配置中设置用户名。

```
// src/app/core/user.service.ts (constructor)
constructor(@Optional() config: UserServiceConfig) {
  if (config) { this._userName = config.userName; }
}
```

下面是一个接受 `UserServiceConfig` 参数的 `forRoot()` 方法：

```
// src/app/core/core.module.ts (forRoot)
static forRoot(config: UserServiceConfig): ModuleWithProviders {
  return {
    ngModule: CoreModule,
    providers: [
      {provide: UserServiceConfig, useValue: config }
    ]
  };
}
```

最后，在 `AppModule` 的 `imports`*列表*中调用它。

```
// src/app/app.module.ts (imports)
import { CoreModule } from './core/core.module';
/* . . . */
@NgModule({
  imports: [
    BrowserModule,
    ContactModule,
    CoreModule.forRoot({userName: 'Miss Marple'}),
    AppRoutingModule
  ],
/* . . . */
})
export class AppModule { }
```

Remember to *import* `CoreModule` as a Javascript import at the top of the file; don't add it to more than one `@NgModule` `imports` list.

### 防止重复导入 CoreModule

Only the root `AppModule` should import the `CoreModule`. If a lazy-loaded module imports it too, the app can generate [multiple instances](https://www.angular.cn/guide/ngmodule-faq#q-why-bad) of a service.

要想防止惰性加载模块重复导入 `CoreModule`，可以添加如下的 `CoreModule` 构造函数。

```
// src/app/core/core.module.ts
constructor (@Optional() @SkipSelf() parentModule: CoreModule) {
  if (parentModule) {
    throw new Error(
      'CoreModule is already loaded. Import it in the AppModule only');
  }
}
```

The constructor tells Angular to inject the `CoreModule` into itself. The injection would be circular if Angular looked for `CoreModule` in the *current* injector. The `@SkipSelf` decorator means "look for `CoreModule` in an ancestor injector, above me in the injector hierarchy."

如果构造函数在 `AppModule` 中执行，那就没有祖先注入器能提供 `CoreModule` 的实例，于是注入器就会放弃查找。

默认情况下，当注入器找不到想找的提供商时，会抛出一个错误。但 `@Optional` 装饰器表示找不到该服务也无所谓。于是注入器会返回 `null`，`parentModule` 参数也就被赋成了空值，而构造函数没有任何异常。

但如果你把 `CoreModule` 导入到像 `CustomerModule` 这样的惰性加载模块中，事情就不一样了。

Angular 会创建一个惰性加载模块，它具有自己的注入器，它是根注入器的*子注入器*。 `@SkipSelf` 让 Angular 在其父注入器中查找 `CoreModule`，这次，它的父注入器却是根注入器了（而上次的父注入器是空）。 当然，这次它找到了由根模块 `AppModule` 导入的实例。 该构造函数检测到存在 `parentModule`，

## 惰性加载的特性模块

### High level view

要想建立一个惰性加载的特性模块，有三个主要步骤：

1. 创建该特性模块。
2. 创建该特性模块的路由模块。
3. Configure the routes.

### 建立应用

```
ng new customer-app --routing
```

### 创建一个带路由特性的模块

```
ng generate module customers --routing
```

### 向特性模块中添加组件

```
ng generate component customers/customer-list
```

### 加一个特性模块

```
ng generate module orders --routing
ng generate component orders/order-list
```

### 建立 UI

### 配置路由

这两个特性模块（`OrdersModule` 和 `CustomersModule`）应该挂接到 `AppRoutingModule` 中，来让路由器知道它们。其结构如下：

![lazy loaded modules diagram](https://www.angular.cn/generated/images/guide/lazy-loading-ngmodules/lazy-load-relationship.jpg)

每个特性模块都是路由器中的一个“门口”。在 `AppRoutingModule` 中，你配置了一些路由指向这些特性模块（即 `OrderModule` 和 `CustomersModule`）。
通过这种方式，路由器就知道了如何跳转到特性模块。然后，特性模块就把 `AppRoutingModule` 和 `CustomersRoutingModule` 或 `OrdersRoutingModule` 连接到一起。这些路由模块会告诉路由器该到哪里去加载相应的组件。

#### 顶层的路由

在 `AppRoutingModule` 中，把 `routes` 数组修改成这样：

```
// src/app/app-routing.module.ts
const routes: Routes = [
  {
    path: 'customers',
    loadChildren: './customers/customers.module#CustomersModule'
  },
  {
    path: 'orders',
    loadChildren: './orders/orders.module#OrdersModule'
  },
  {
    path: '',
    redirectTo: '',
    pathMatch: 'full'
  }
];
```

这些 `import` 语句没有变化。前两个路径分别路由到了 `CustomersModule` 和 `OrdersModule`。注意看惰性加载的语法：`loadChildren` 后面紧跟着一个字符串，它指向模块的相对路径，然后是一个 `#`，然后是该模块的类名。

#### 特性模块内部

特性模块就像是 `AppRoutingModule` 和该特性自己的路由模块之间的连接器。`AppRoutingModule` 导入了特性模块 `CustomersModule`，而 `CustomersModule` 又导入了 `CustomersRoutingModule`。

```
// src/app/customers/customers.module.ts
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { CustomersRoutingModule } from './customers-routing.module';
import { CustomerListComponent } from './customer-list/customer-list.component';

@NgModule({
  imports: [
    CommonModule,
    CustomersRoutingModule
  ],
  declarations: [CustomerListComponent]
})
export class CustomersModule { }
```

`customers.module.ts` 文件导入了 `CustomersRoutingModule` 和 `CustomerListComponent`，所以 `CustomersModule` 类可以访问它们。接着 `CustomersRoutingModule` 出现在了 `@NgModule` 的 `imports` 数组中，这让 `CustomersModule` 可以访问它的路由模块。而 `CustomerListComponent` 出现在了`declarations` 数组中，这表示 `CustomerListComponent` 属于 `CustomersModule`。

### 配置该特性模块的路由

接下来的步骤位于 `customers-routing.module.ts` 中。首先，在文件的顶部使用 JS 的 `import` 语句导入该组件。然后添加指向 `CustomerListComponent` 的路由。

```
// src/app/customers/customers-routing.module.ts
import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { CustomerListComponent } from './customer-list/customer-list.component';


const routes: Routes = [
  {
    path: '',
    component: CustomerListComponent
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class CustomersRoutingModule { }
```

`path` 被设置成了空字符串。这是因为 `AppRoutingModule` 中的路径已经设置为了 `customers`，所以 `CustomersRoutingModule` 中的这个路由定义已经位于 `customers` 这个上下文中了。也就是说这个路由模块中的每个路由其实都是子路由。

重复这个步骤以导入 `OrdersListComponent`，并为 `orders-routing.module.ts` 配置路由树组：

```
// src/app/orders/orders-routing.module.ts (excerpt)
import { OrderListComponent } from './order-list/order-list.component';

const routes: Routes = [
  {
    path: '',
    component: OrderListComponent
  }
];
```

### forRoot() 与 forChild()

你可能已经注意到了，CLI 会把 `RouterModule.forRoot(routes)` 添加到 `app-routing.module.ts` 的 `imports` 数组中。 这会让 Angular 知道 `AppRoutingModule` 是一个路由模块，而 `forRoot()` 表示这是一个根路由模块。 它会配置你传入的所有路由、让你能访问路由器指令并注册 `RouterService`。 在 `AppRoutingModule` 中使用 `forRoot()`，在本应用中这只会在顶层模块中写一次。

CLI 还会把 `RouterModule.forChild(routes)` 添加到各个特性模块中。这种方式下 Angular 就会知道这个路由列表只负责提供额外的路由并且其设计意图是作为特性模块使用。你可以在多个模块中使用 `forChild()`。

`forRoot()` 包含的注入器配置是全局性的，比如对路由器的配置。`forChild()` 中没有注入器配置，只有像 `RouterOutlet` 和 `RouterLink` 这样的指令。 ???

## 共享特性模块

创建共享模块能让你更好地组织和梳理代码。你可以把常用的指令、管道和组件放进一个模块中，然后在应用中其它需要这些的地方导入该模块。

Consider the following module from an imaginary app:

```
import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { CustomerComponent } from './customer.component';
import { NewItemDirective } from './new-item.directive';
import { OrdersPipe } from './orders.pipe';

@NgModule({
 imports:      [ CommonModule ],
 declarations: [ CustomerComponent, NewItemDirective, OrdersPipe ],
 exports:      [ CustomerComponent, NewItemDirective, OrdersPipe,
                 CommonModule, FormsModule ]
})
export class SharedModule { }
```

Note the following:

-  它导入了 `CommonModule`，因为该模块需要一些常用指令。
-  它声明并导出了一些工具性的管道、指令和组件类。
-  它重新导出了 `CommonModule` 和 `FormsModule`

通过重新导出 `CommonModule` 和 `FormsModule`，任何导入了这个 `SharedModule` 的其它模块，就都可以访问来自 `CommonModule` 的 `NgIf` 和 `NgFor` 等指令了，也可以绑定到来自 `FormsModule` 中的 `[(ngModel)]` 的属性了。

即使 `SharedModule` 中声明的组件没有绑定过 `[(ngModel)]`，而且`SharedModule` 也不需要导入 `FormsModule`，`SharedModule` 仍然可以导出 `FormsModule`，而不必把它列在 `imports` 中。 这种方式下，你可以让其它模块也能访问 `FormsModule`，而不用直接在自己的 `@NgModule` 装饰器中导入它。

### 使用来自其它模块的组件和服务

在使用来自其它模块的组件和来自其它模块的服务时，有一个很重要的区别。当你要使用指令、管道和组件时，导入那些模块就可以了。而导入带有服务的模块意味着你会拥有那个服务的一个新实例，这通常不会是你想要的结果（你通常会想取到现存的服务）。使用模块导入来控制服务的实例化。

获取共享服务的最常见方式是通过 Angular 的[依赖注入系统](https://www.angular.cn/guide/dependency-injection)，而不是模块系统（导入模块将导致创建新的服务实例，那不是典型的用法）。要进一步了解共享服务，参见[服务提供商](https://www.angular.cn/guide/providers)。

## NgModule API

### `@NgModule` 的设计意图

宏观来讲，NgModule 是组织 Angular 应用的一种方式，它们通过 `@NgModule` 装饰器中的元数据来实现这一点。 这些元数据可以分成三类：

-  **静态的：**编译器配置，用于告诉编译器指令的选择器并通过选择器匹配的方式决定要把该指令应用到模板中的什么位置。它是通过 `declarations` 数组来配置的。
-  **运行时：**通过 `providers` 数组提供给注入器的配置。
-  **组合/分组：**通过 `imports` 和 `exports` 数组来把多个 NgModule 放在一起，并彼此可用。

```
@NgModule({
  // Static, that is compiler configuration
  declarations: [], // Configure the selectors
  entryComponents: [], // Generate the host factory

  // Runtime, or injector configuration
  providers: [], // Runtime injector configuration

  // Composability / Grouping
  imports: [], // composing NgModules together
  exports: [] // making NgModules available to other parts of the app
})
```

### @NgModule 元数据

| 属性              | 说明                                                         |
| ----------------- | ------------------------------------------------------------ |
| `declarations`    | *属于该模块*的[可声明对象](https://www.angular.cn/guide/ngmodule-faq#q-declarable)（*组件*、*指令*和*管道*）的列表。                              当编译模板时，你需要确定一组选择器，它们将用于触发相应的指令。                              The template is compiled within the context of an NgModule —— 模板的组件是在该 NgModule 内部声明的，它会使用如下规则来确定这组选择器：                                          列在 `declarations` 中的所有指令选择器。                                            从所导入的 NgModule 中导出的那些指令的选择器。                                                组件、指令和管道*只能*属于一个模块。 如果尝试把同一个类声明在多个模块中，编译器就会报告一个错误。 小心，不要重复声明从其它模块中直接或间接导入的类。 |
| `providers`       | 依赖注入提供商的列表。        Angular 会使用该模块的注入器注册这些提供商。 如果该模块是启动模块，那就会使用根注入器。        These services become available for injection into any component, directive, pipe or service which is a child of this injector.        惰性加载模块有自己的注入器，它通常是应用的根注入器的子注入器。        惰性加载的服务是局限于这个惰性加载模块的注入器中的。 如果惰性加载模块也提供了 `UserService`，那么在这个模块的上下文中创建的任何组件（比如在路由器导航时），都会获得这个服务的本模块内实例，而不是来自应用的根注入器的实例。        Components in external modules continue to receive the instance provided by their injectors        要深入了解关于多级注入器及其作用域，参见[服务提供商](https://www.angular.cn/guide/providers)。 |
| `imports`         | A list of modules which should be folded into this module. Folded means it is as if all the imported NgModule's exported properties were declared here.       Specifically, it is as if the list of modules whose exported components, directives, or pipes are referenced by the component templates were declared in this module.        组件模板可以[引用](https://www.angular.cn/guide/ngmodule-faq#q-template-reference)其它组件、指令或管道，不管它们是在本模块中声明的，还是从导入的模块中导出的。 比如，只有当该模块导入了 Angular 的 `CommonModule（也可能从`BrowserModule`中间接导入）时，组件才能使用`NgIf`和`NgFor` 指令。        你可以从 `CommonModule` 中导入很多标准指令，不过也有些常用的指令属于其它模块。 比如，你只有导入了 Angular 的 `FormsModule` 时才能使用 `[(ngModel)]`。 |
| `exports`         | A list of declarations—*component*, *directive*, and *pipe* classes—that an importing module can use.       Exported declarations are the module's *public API*. A component in another module can [use](https://www.angular.cn/guide/ngmodule-faq#q-template-reference) *this* module's `UserComponent` if it imports this module and this module exports `UserComponent`。        默认情况下这些可声明对象都是私有的。 如果本模块*没有*导出 `UserComponent`，那么就只有*本*模块中的组件才能使用 `UserComponent`。        导入某个模块*并不会*自动重新导出被导入模块的那些导入。 模块 B 不会因为它导入了模块 A，而模块 A 导入了 `CommonModule` 而能够使用 `ngIf`。 模块 B 必须自己导入 `CommonModule`。        一个模块可以把另一个模块加入自己的 `exports` 列表中，这时，另一个模块的所有公共组件、指令和管道都会被导出。        [重新导出](https://www.angular.cn/guide/ngmodule-faq#q-reexport)可以让模块被显式传递。 如果模块 A 重新导出了 `CommonModule`，而模块 B 导入了模块 A，那么模块 B 就可以使用 `ngIf` 了 —— 即使它自己没有导入 `CommonModule`。 |
| `bootstrap`       | 要自动启动的组件列表。        通常，在这个列表中只有一个组件，也就是应用的*根组件*。        Angular 也可以引导多个引导组件，它们每一个都在宿主页面中有自己的位置。        启动组件会自动添加到 `entryComponents` 中。 |
| `entryComponents` | 那些可以动态加载进视图的组件列表。        默认情况下，Angular 应用至少有一个入口组件，也就是根组件 `AppComponent`。 它用作进入该应用的入口点，也就是说你通过引导它来启动本应用。        路由组件也是*入口组件*，因为你需要动态加载它们。 路由器创建它们，并把它们扔到 DOM 中的 `<router-outlet>` 附近。        虽然引导组件和路由组件都是*入口组件*，不过你不用自己把它们加到模块的 `entryComponents` 列表中，因为它们会被隐式添加进去。        Angular 会自动把模块的 `bootstrap` 中的组件和路由定义中的组件添加到 `entryComponents` 列表。        而那些使用不易察觉的[`ViewComponentRef.createComponent()`](https://angular.cn/api/core/ViewContainerRef#createComponent)的方式进行命令式引导的组件仍然需要添加。        动态组件加载在除路由器之外的大多数应用中都不太常见。如果你需要动态加载组件，就必须自己把那些组件添加到 `entryComponents` 列表中。        要了解更多，参见[入口组件](https://www.angular.cn/guide/entry-components)一章。 |

## NgModule 模块常见问题

### 如果我两次导入同一个模块会怎么样？

没有任何问题。当三个模块全都导入模块'A'时，Angular 只会首次遇到时加载一次模块'A'，之后就不会这么做了。

Angular 不允许模块之间出现循环依赖，所以不要让模块'A'导入模块'B'，而模块'B'又导入模块'A'。

### 为什么在共享模块中为惰性加载模块提供服务是个馊主意？ ???

#### 立即加载的场景

当立即加载的模块提供了服务时，比如 `UserService`，该服务是在全应用级可用的。如果根模块提供了 `UserService`，并导入了另一个也提供了同一个 `UserService` 的模块，Angular 就会把它们中的一个注册进应用的根注入器中（参见[如果两次导入了同一个模块会怎样？](https://www.angular.cn/guide/ngmodule-faq#q-reimport)）。

然后，当某些组件注入 `UserService` 时，Angular 就会发现它已经在应用的根注入器中了，并交付这个全应用级的单例服务。这样不会出现问题。

#### 惰性加载场景 

现在，该考虑 `HeroModule` 了，*它是惰性加载的！*。

当路由器准备惰性加载 `HeroModule` 的时候，它会创建一个子注入器，并且把 `UserService` 的提供商注册到那个子注入器中。子注入器和根注入器是*不同*的。

当 Angular 创建一个惰性加载的 `HeroComponent` 时，它必须注入一个 `UserService`。 这次，它会从惰性加载模块的*子注入器*中查找 `UserService` 的提供商，并用它创建一个 `UserService` 的新实例。 这个 `UserService` 实例与 Angular 在主动加载的组件中注入的那个全应用级单例对象截然不同。

这个场景导致你的应用每次都创建一个新的服务实例，而不是使用单例的服务。

### 为什么惰性加载模块会创建一个子注入器？

归根结底，这来自于 Angular 依赖注入系统的一个基本特征：在注入器还没有被第一次使用之前，可以不断为其添加提供商。一旦注入器已经创建和开始交付服务，它的提供商列表就被冻结了，不再接受新的提供商。

当应用启动时，Angular 会首先使用所有 主动加载模块中的提供商来配置根注入器，这发生在它创建第一个组件以及注入任何服务之前。一旦应用开始工作，应用的根注入器就不再接受新的提供商了。

### 有哪些类型的模块？我应该如何使用它们？

每个应用都不一样。根据不同程度的经验，开发者会做出不同的选择。下列建议和指导原则广受欢迎。

#### SharedModule

为那些可能会在应用中到处使用的组件、指令和管道创建 `SharedModule`。 这种模块应该只包含 `declarations`，并且应该导出几乎所有 `declarations` 里面的声明。

`SharedModule` 可以重新导出其它小部件模块，比如 `CommonModule`、`FormsModule` 和提供你广泛使用的 UI 控件的那些模块。

`SharedModule`**不应该**带有 `providers`，原因[在前面解释过了](https://www.angular.cn/guide/ngmodule-faq#q-why-bad)。 它的导入或重新导出的模块中也不应该有 `providers`。 如果你要违背这条指导原则，请务必想清楚你在做什么，并要有充分的理由。

在任何特性模块中（无论是你在应用启动时主动加载的模块还是之后惰性加载的模块），你都可以随意导入这个 `SharedModule`。

#### CoreModule

为你要在应用启动时加载的那些服务创建一个带 `providers` 的 `CoreModule`。

只能在根模块 `AppModule` 中导入 `CoreModule`。 永远不要在除根模块 `AppModule` 之外的任何模块中导入 `CoreModule`。

考虑把 `CoreModule` 做成一个没有 `declarations` 的纯服务模块。

要了解更多，参见[共享模块](https://www.angular.cn/guide/sharing-ngmodules)和[单例服务](https://www.angular.cn/guide/singleton-services)。