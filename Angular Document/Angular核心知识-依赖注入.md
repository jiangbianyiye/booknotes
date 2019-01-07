



# Angular 核心知识-依赖注入

## Angular 依赖注入

Dependency injection (DI), is an important application design pattern. Dependencies are services or objects that a class needs to perform its function. DI is a coding pattern in which a class asks for dependencies from external sources rather than creating them itself. 

在 Angular 中，DI 框架会在实例化该类时向其提供这个类所声明的依赖项。

### 创建和注册可注入的服务

The DI framework lets you supply data to a component from an injectable *service* class, defined in its own file.

> 在同一个文件中放多个类容易让人困惑。我们通常建议你在单独的文件中定义组件和服务。
>
> 如果你把组件和服务都放在同一个文件中，请务必先定义服务，然后再定义组件。如果在服务之前定义组件，则会在运行时收到一个空引用错误。
>
> 也可以借助 `forwardRef()` 方法来先定义组件，就像[这个博客](http://blog.thoughtram.io/angular/2015/09/03/forward-references-in-angular-2.html)中解释的那样。
>
> 你还可以使用前向引用来打破循环依赖，参见 [DI 一章](https://www.angular.cn/guide/dependency-injection-in-action#forwardref)中的例子。

#### 创建可注入的服务类

[Angular CLI](https://www.angular.cn/cli) 可以用下列命令在 `src/app/heroes` 目录下生成一个新的 `HeroService` 类。

```
ng generate service heroes/hero
```

The command creates the following `HeroService` skeleton.

```
// src/app/heroes/hero.service.ts (CLI-generated)
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class HeroService {
  constructor() { }
}
```

`@Injectable()` 是每个 Angular 服务定义中的基本要素。该类的其余部分导出了一个 `getHeroes` 方法，它会返回像以前一样的模拟数据。（真实的应用可能会从远程服务器中异步获取这些数据。）

```
// src/app/heroes/hero.service.ts
import { Injectable } from '@angular/core';
import { HEROES } from './mock-heroes';

@Injectable({
  // we declare that this service should be created
  // by the root application injector.
  providedIn: 'root',
})
export class HeroService {
  getHeroes() { return HEROES; }
}
```

#### 用服务提供商配置注入器

The class we have created provides a service. The `@Injectable()` decorator marks it as a service
that can be injected, but Angular can't actually inject it anywhere until you configure
an Angular [dependency injector](https://www.angular.cn/guide/glossary#injector) with a [provider](https://www.angular.cn/guide/glossary#provider) of that service. 

The injector is responsible for creating service instances and injecting them into classes like `HeroListComponent`. You rarely create an Angular injector yourself. Angular creates injectors for you as it executes the app, starting with the *root injector* that it creates during the [bootstrap process](https://www.angular.cn/guide/bootstrapping).

A provider tells an injector *how to create the service*. You must configure an injector with a provider before that injector can create a service (or provide any other kind of dependency). 

A provider can be the service class itself, so that the injector can use `new` to create an instance. You might also define more than one class to provide the same service in different ways, and configure different injectors with different providers.

> Injectors are inherited, which means that if a given injector can't resolve a dependency, it asks the parent injector to resolve it. A component can get services from its own injector, from the injectors of its component ancestors, from the injector of its parent NgModule, or from the `root` injector. 
>
> Learn more about the [different kinds of providers](https://www.angular.cn/guide/dependency-injection-providers).
>
> Learn more about  how the [injector hierarchy](https://www.angular.cn/guide/hierarchical-dependency-injection) works.

You can configure injectors with providers at different levels of your app, by setting a metadata value in one of three places:

- 在服务本身的 `@Injectable()` 装饰器中。
- 在 NgModule 的 `@NgModule()` 装饰器中。
- 在组件的 `@Component()` 装饰器中。

`@Injectable()` 装饰器具有一个名叫 `providedIn` 的元数据选项，在那里你可以指定把被装饰类的提供商放到 `root` 注入器中，或某个特定 NgModule 的注入器中。

`@NgModule()` 和 `@Component()` 装饰器都有用一个 `providers` 元数据选项，在那里你可以配置 NgModule 级或组件级的注入器。

### 注入服务

`HeroListComponent` 要想从 `HeroService` 中获取英雄列表，就得要求注入 `HeroService`，而不是自己使用 `new` 来创建自己的 `HeroService` 实例。

你可以通过制定**带有依赖类型的构造函数参数**来要求 Angular 在组件的构造函数中注入依赖项。

```
// src/app/heroes/hero-list.component (constructor signature)
constructor(heroService: HeroService)
```

`HeroService` must provided in some parent injector. The code in `HeroListComponent` doesn't depend on where `HeroService` comes from. If you decided to provide `HeroService` in `AppModule`, `HeroListComponent` wouldn't change.

#### 注入器与服务实例

Services are singletons *within the scope of an injector*. That is, there is at most one instance of a service in a given injector. 

应用只有一个根注入器。在 `root` 或 `AppModule` 级提供 `UserService` 意味着它注册到了根注入器上。
在整个应用中只有一个 `UserService` 实例，每个要求注入 `UserService` 的类都会得到这一个服务实例，*除非*你在*子注入器*中配置了另一个提供商。

Angular DI has a [hierarchical injection system](https://www.angular.cn/guide/hierarchical-dependency-injection), which means that nested injectors can create their own service instances. Angular regularly creates nested injectors. Whenever Angular creates a new instance of a component that has `providers` specified in `@Component()`, it also creates a new *child injector* for that instance. Similarly, when a new NgModule is lazy-loaded at run time, Angular can create an injector for it with its own providers. 

Child modules and component injectors are independent of each other, and create their own separate instances of the provided services. When Angular destroys an NgModule or component instance, it also destroys that injector and that injector's service instances. 

Thanks to [injector inheritance](https://www.angular.cn/guide/hierarchical-dependency-injection), you can still inject application-wide services into these components.
A component's injector is a child of its parent component's injector, and a descendent of its parent's injector, and so on all the way back to the application's *root* injector. Angular can inject a service provided by any injector in that lineage.

For example, Angular can inject `HeroListComponent` with both the `HeroService` provided in `HeroComponent` and the `UserService` provided in `AppModule`.

### 测试带有依赖的组件

基于依赖注入设计一个类，能让它更易于测试。 要想高效的测试应用的各个部分，你所要做的一切就是把这些依赖列到构造函数的参数表中而已。

For example, you can create a new `HeroListComponent` with a mock service that you can manipulate
under test.

```
// src/app/test.component.ts
const expectedHeroes = [{name: 'A'}, {name: 'B'}]
const mockService = <HeroService> {getHeroes: () => expectedHeroes }

it('should have heroes when HeroListComponent created', () => {
  // Pass the mock to the constructor as the Angular injector would
  const component = new HeroListComponent(mockService);
  expect(component.heroes.length).toEqual(expectedHeroes.length);
});
```

Learn more in the [Testing](https://www.angular.cn/guide/testing) guide.

### Services that need other services

服务还可以具有自己的依赖。`HeroService` 非常简单，没有自己的依赖。不过，如果你希望通过日志服务来报告这些活动，那么就可以使用同样的*构造函数注入*模式，添加一个构造函数来接收一个 `Logger` 参数。

这是修改后的 `HeroService`，它注入了 `Logger`

```
// src/app/heroes/hero.service
import { Injectable } from '@angular/core';
import { HEROES }     from './mock-heroes';
import { Logger }     from '../logger.service';

@Injectable({
  providedIn: 'root',
})
export class HeroService {

  constructor(private logger: Logger) {  }

  getHeroes() {
    this.logger.log('Getting heroes ...');
    return HEROES;
  }
}
```

```
// src/app/logger.service
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class Logger {
  logs: string[] = []; // capture logs for testing

  log(message: string) {
    this.logs.push(message);
    console.log(message);
  }
}
```

When Angular creates a class whose constructor has parameters, it looks for type and injection metadata about those parameters so that it can inject the correct service. If Angular can't find that parameter information, it throws an error. Angular can only find the parameter information *if the class has a decorator of some kind*. The `@Injectable()` decorator is the standard decorator for service classes.

>  The decorator requirement is imposed by TypeScript. TypeScript normally discards parameter type information when it [transpiles](https://www.angular.cn/guide/glossary#transpile) the code to JavaScript. TypeScript preserves this information if the class has a decorator and the `emitDecoratorMetadata` compiler option is set `true` in TypeScript's `tsconfig.json` configuration file. The CLI configures `tsconfig.json` with `emitDecoratorMetadata: true`.
>
>  This means you're responsible for putting `@Injectable()` on your service classes.

#### 依赖注入令牌

When you configure an injector with a provider, you associate that provider with a [DI token](https://www.angular.cn/guide/glossary#di-token). The injector maintains an internal *token-provider* map that it references when asked for a dependency. The token is the key to the map.

In simple examples, the dependency value is an *instance*, and the class *type* serves as its own lookup key. Here you get a `HeroService` directly from the injector by supplying the `HeroService` type as the token:

```
// src/app/injector.component.ts
heroService: HeroService;
```

The behavior is similar when you write a constructor that requires an injected class-based dependency.
When you define a constructor parameter with the `HeroService` class type, Angular knows to inject the service associated with that `HeroService` class token:

```
// src/app/heroes/hero-list.component.ts
constructor(heroService: HeroService)
```

Many dependency values are provided by classes, but not all. The expanded *provide* object lets you associate different kinds of providers with a DI token. Learn more about [different kinds of providers](https://www.angular.cn/guide/dependency-injection-providers).

#### 可选依赖

当组件或服务声明某个依赖项时，该类的构造函数会以参数的形式接收那个依赖项。 通过给这个参数加上 `@Optional()` 注解，你可以告诉 Angular，该依赖是可选的。

```
import { Optional } from '@angular/core';
```

```
constructor(@Optional() private logger: Logger) {
  if (this.logger) {
    this.logger.log(some_message);
  }
}
```

当使用 `@Optional()` 时，你的代码必须能正确处理 null 值。如果你没有在任何地方注册过 logger 提供商，那么注入器就会把 `logger` 的值设置为 null。

```
@Inject() and @Optional() are parameter decorators. They alter the way the DI framework provides a dependency, by annotating the dependency parameter on the constructor of the class that requires the dependency.
Learn more about parameter decorators in Hierarchical Dependency Injectors.
```

## 多级注入器

Angular 的依赖注入系统是*多级的*。实际上，应用程序中有一个与组件树平行的注入器树（译注：平行是指结构完全相同且一一对应）。你可以在组件树中的任何级别上重新配置注入器。

### Where to configure providers

You can configure providers for different injectors in the injector hierarchy. An internal platform-level injector is shared by all running apps. The `AppModule` injector is the root of an app-wide injector hierarchy, and within an NgModule, directive-level injectors follow the structure of the component hierarchy.

The choices you make about where to configure providers lead to differences in the final bundle size, service *scope*, and service *lifetime*.

When you specify providers in the `@Injectable()`  decorator of the service itself (typically at the app root level),  optimization tools such as those used by the CLI's production builds can  perform *tree shaking*, which removes services that aren't used by your app. Tree shaking results in smaller bundle sizes.  Learn more about [tree-shakable providers](https://www.angular.cn/guide/dependency-injection-providers#tree-shakable-providers).

你可能会在应用程序的许多地方注入 `UserService`，并希望每次注入的都是服务的同一个实例。这种情况下，通过 `root` 来提供 `UserService` 就是不错的选择，而且这也是 [Angular CLI](https://www.angular.cn/cli) 为应用生成服务时的默认选项。'

> 平台注入器
>
> 当使用 providedIn:'root' 时，你是在配置应用的根注入器，也就是 AppModule 的注入器。 整个注入器树的真正的根是平台注入器，它是根注入器的父节点。 这可以让多个应用共享同一套平台配置。比如，无论你正在运行多少个应用，一个浏览器窗口都只有一个地址栏。
>
> 平台注入器是在启动期间内部使用的，用于配置与平台相关的依赖项。通过在调用 platformBrowser() 函数时提供 extraProviders 参数，你可以在平台级配置更多与平台相关的提供商。
>
> 要了解借助注入器树解析依赖项的更多信息，参见你所不知道的 Angular 依赖注入树。

**NgModule-level** providers can be specified with `@NgModule()` `providers` metadata option, or in the `@Injectable()` `providedIn` option (with some module other than the root `AppModule`).

Use the `@NgModule()` `provides` option if a module is [lazy loaded](https://www.angular.cn/guide/lazy-loading-ngmodules).  The module's own injector is configured with the provider when that  module is loaded, and Angular can inject the corresponding services in  any class it creates in that module. If you use the `@Injectable()` option `providedIn: MyLazyloadModule`, the provider could be shaken out at compile time, if it is not used anywhere else in the app.  Learn more about [tree-shakable providers](https://www.angular.cn/guide/dependency-injection-providers#tree-shakable-providers).

For both root-level and module-level  injectors, a service instance lives for the life of the app or module,  and Angular injects this one service instance in every class that needs  it.

**Component-level** providers configure each component instance's own injector. Angular can only inject the corresponding services in that component instance or one of its descendant component instances. Angular can't inject the same service instance anywhere else. 

组件提供的服务具有受限的生命周期。 该组件的每个新实例都会获得自己的一份服务实例。 当销毁组件实例时，服务实例也会被同时销毁。

在这个范例应用中，应用一启动就会创建 `HeroComponent` 的实例，而且永不销毁，所以由 `HeroComponent` 创建的 `HeroService` 的实例的生命周期也和应用相同。 如果你要把 `HeroService` 的访问权限制到 `HeroComponent` 及其内嵌的 `HeroListComponent` 中，可以通过修改 `HeroComponent` 的元数据，来要求在组件级提供 `HeroService`。参见稍后的[组件级注入的例子](https://www.angular.cn/guide/hierarchical-dependency-injection#component-injectors)。

#### 在 @Injectable 级进行配置

The `@Injectable()` decorator identifies every service class. The `providedIn` metadata option for a service class configures a specific injector (typically `root`) to use the decorated class as a provider of the service. When an injectable class provides its own service to the `root` injector, the service is available anywhere the class is imported. 

下面的例子使用类上的 `@Injectable()` 装饰器为 `HeroService` 配置了提供商。

```
// src/app/heroes/heroes.service.ts
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class HeroService {
  constructor() { }
}
```

This configuration tells Angular that the app's root injector is responsible for creating an instance of `HeroService` by invoking its constructor, and for making that instance available across the application. 

Providing a service with the app's root injector is a typical case, and the CLI sets up this kind of a provider automatically for you when generating a new service. However, you might not always want to provide your service at the root level. You might, for instance, want users to explicitly opt-in to using the service.

Instead of specifying the `root` injector, you can set `providedIn` to a specific NgModule. 

比如，在下面的代码片段中，`@Injectable()` 装饰器配置了一个提供商，它能用于 `HeroModule` 包含的所有注入器中。

```
// src/app/heroes/hero.service.ts
import { Injectable } from '@angular/core';
import { HeroModule } from './hero.module';
import { HEROES } from './mock-heroes';

@Injectable({
  // we declare that this service should be created
  // by any injector that includes HeroModule.
  providedIn: HeroModule,
})
export class HeroService {
  getHeroes() { return HEROES; }
}
```

一般来说，这和在 NgModule 本身的装饰器上配置注入器没有多少不同，主要的区别是如果 NgModule 没有用到该服务，那么它就是可以被摇树优化掉的。对于某个提供特定服务的库而言，有些组件*可能*会希望注入器是可选的，等使用该库的应用程序来决定是否要提供该服务。欲知详情，参见[可摇树优化的提供商](https://www.angular.cn/guide/dependency-injection-providers#tree-shakable-providers)。

#### @NgModule 级注入器

你还可以在非根 NgModule 元数据的 `providedIn` 选项中配置一个模块级的提供商，以便把该服务的范围限定到该模块一级。这和在 `@Injectable()` 元数据中指定一个非根模块是基本等效的，但以这种方式提供的服务无法被摇树优化掉。

You generally don't need to specify `AppModule` with `providedIn`, because the app's `root` injector is the `AppModule` injector. However, if you configure a app-wide provider in the`@NgModule()` metadata for `AppModule`, it overrides one configured for `root` in the `@Injectable()` metadata. You can do this to configure a non-default provider of a service that is shared with multiple apps. 

下面的例子中，通过把 [location 策略](https://www.angular.cn/guide/router#location-strategy) 的提供商添加到 `AppModule` 的 `providers` 列表中，为路由器配置了非默认的 [location 策略](https://www.angular.cn/guide/router#location-strategy)。

```
// src/app/app.module.ts (providers)
providers: [
  { provide: LocationStrategy, useClass: HashLocationStrategy }
]
```

> [LocationStrategy](https://www.angular.cn/api/common/LocationStrategy)    [HashLocationStrategy](https://www.angular.cn/api/common/HashLocationStrategy)

#### @Component 级注入器

Individual components within an NgModule have their own injectors. You can limit the scope of a provider to a component and its children by configuring the provider at the component level using the `@Component` metadata.

The following example is a revised `HeroesComponent` that specifies `HeroService` in its `providers` array. `HeroService` can provide heroes to instances of this component, or to any child component instances. 

```
// src/app/heroes/heroes.component.ts
import { Component } from '@angular/core';

import { HeroService } from './hero.service';

@Component({
  selector: 'app-heroes',
  providers: [ HeroService ],
  template: `
    <h2>Heroes</h2>
    <app-hero-list></app-hero-list>
  `
})
export class HeroesComponent { }
```

#### 元素注入器

An injector does not actually belong to a component, but rather to the component instance's anchor element in the DOM. A different component instance on a different DOM element uses a different injector. ???

Components are a special type of directive, and the `providers` property of `@Component()` is inherited from `@Directive()`. Directives can also have dependencies, and you can configure providers in their `@Directive()` metadata. When you configure a provider for a component or directive using the `providers`  property, that provider belongs to the injector for the anchor DOM  element. Components and directives on the same element share an  injector.

- Learn more about [Element Injectors in Angular](https://blog.angularindepth.com/a-curios-case-of-the-host-decorator-and-element-injectors-in-angular-582562abcf0a).

### 注入器冒泡

当一个组件申请获得一个依赖时，Angular 先尝试用该组件自己的注入器来满足它。 如果该组件的注入器没有找到对应的提供商，它就把这个申请转给它父组件的注入器来处理。 如果那个注入器也无法满足这个申请，它就继续转给它在注入器树中的父注入器。 这个申请继续往上冒泡 —— 直到找到了一个能处理此申请的注入器或者超出了组件树中的祖先位置为止。 如果超出了组件树中的祖先还未找到，Angular 就会抛出一个错误。

如果你在不同的层级上为同一个 DI 令牌注册了提供商，那么 Angular 所碰到的第一个注入器就会用来提供该依赖。 比如，如果提供商注册在该组件的本地注入器上，那么当该组件需要这个服务时，Angular 就不会去找能提供同一服务的其它提供商。

> 你可以通过在构造函数的依赖项参数上添加参数装饰器 `@Host()` 来限制冒泡。 当搜索提供商时，就会在组件宿主元素的注入器处停下。
>
> - 参见这个同时使用 `@Host` 和 `@Optional` 的[例子](https://www.angular.cn/guide/dependency-injection-in-action#qualify-dependency-lookup)，另一个参数装饰器 `@Optional` 让你能在没有找到提供商时把参数置为 null。
> - 到 [`@Host` 装饰器与元素注入器](https://blog.angularindepth.com/a-curios-case-of-the-host-decorator-and-element-injectors-in-angular-582562abcf0a) 中了解更多。

If you only register providers with the root injector at the top level (typically the root `AppModule`), the tree of injectors appears to be flat. All requests bubble up to the root injector, whether you configured it with the `bootstrapModule` method, or registered all providers with `root` in their own services.

### 组件注入器

在不同层次上重新配置一个或多个提供商的能力，开启了一些既有趣又有用的可能性。

#### 场景: 服务隔离

出于架构方面的考虑，可能会让你决定把一个服务限制到只能在它所属的特定领域中访问。

如果你在根模块 `AppModule` 中（也就是你注册 `HeroesService` 的地方）提供 `VillainsService`，就会让应用中的任何地方都能访问到 `VillainsService`，包括针对英雄的工作流。如果你稍后修改了 `VillainsService`，就可能破坏了英雄组件中的某些地方。在根模块 `AppModule` 中提供该服务将会引入此风险。

你可以在 `VillainsListComponent` 的 `providers` 元数据中提供 `VillainsService`，就像这样：

```
// src/app/villains-list.component.ts (metadata)
@Component({
  selector: 'app-villains-list',
  templateUrl: './villains-list.component.html',
  providers: [ VillainsService ]
})
```

在 `VillainsListComponent` 的元数据中而不是其它地方提供 `VillainsService` 服务，该服务就会只在 `VillainsListComponent` 及其子组件树中可用。它仍然是单例，但是这个单例只存在于*反派（villain）*这个领域中。 你可以确信英雄组件不会访问它，因此减少了犯错误的机会。

#### 场景：多重编辑会话

很多应用允许用户同时进行多个任务。比如，在纳税申报应用中，申报人可以打开多个报税单，随时可能从一个切换到另一个。

每个报税单组件都有下列特征：

-  属于它自己的报税单会话。
-  可以修改一个报税单，而不会影响另一个组件中的申报单。
-  能把所做的修改保存到它的报税单中，或者放弃它们。

假设 `HeroTaxReturnComponent` 还有一些管理并还原这些更改的逻辑。 这对于简单的报税单来说是很容易的。 不过，在现实世界中，报税单的数据模型非常复杂，对这些修改的管理可能不得不投机取巧。 你可以把这种管理任务委托给一个辅助服务，就像这个例子中所做的。

这是一个报税单服务 `HeroTaxReturnService`。 它缓存了单条 `HeroTaxReturn`，用于跟踪那个申报单的变更，并且可以保存或还原它。 它还委托给了全应用级的单例服务 `HeroService`，它是通过依赖注入机制取得的。

```
// src/app/hero-tax-return.service.ts
import { Injectable }    from '@angular/core';
import { HeroTaxReturn } from './hero';
import { HeroesService } from './heroes.service';

@Injectable()
export class HeroTaxReturnService {
  private currentTaxReturn: HeroTaxReturn;
  private originalTaxReturn: HeroTaxReturn;

  constructor(private heroService: HeroesService) { }

  set taxReturn (htr: HeroTaxReturn) {
    this.originalTaxReturn = htr;
    this.currentTaxReturn  = htr.clone();
  }

  get taxReturn (): HeroTaxReturn {
    return this.currentTaxReturn;
  }

  restoreTaxReturn() {
    this.taxReturn = this.originalTaxReturn;
  }

  saveTaxReturn() {
    this.taxReturn = this.currentTaxReturn;
    this.heroService.saveTaxReturn(this.currentTaxReturn).subscribe();
  }
}
```

下面是正在使用它的 `HeroTaxReturnComponent` 组件。

```
// src/app/hero-tax-return.component.ts
import { Component, EventEmitter, Input, Output } from '@angular/core';
import { HeroTaxReturn }        from './hero';
import { HeroTaxReturnService } from './hero-tax-return.service';

@Component({
  selector: 'app-hero-tax-return',
  templateUrl: './hero-tax-return.component.html',
  styleUrls: [ './hero-tax-return.component.css' ],
  providers: [ HeroTaxReturnService ]
})
export class HeroTaxReturnComponent {
  message = '';

  @Output() close = new EventEmitter<void>();

  get taxReturn(): HeroTaxReturn {
    return this.heroTaxReturnService.taxReturn;
  }

  @Input()
  set taxReturn (htr: HeroTaxReturn) {
    this.heroTaxReturnService.taxReturn = htr;
  }

  constructor(private heroTaxReturnService: HeroTaxReturnService) { }

  onCanceled()  {
    this.flashMessage('Canceled');
    this.heroTaxReturnService.restoreTaxReturn();
  };

  onClose()  { this.close.emit(); };

  onSaved() {
    this.flashMessage('Saved');
    this.heroTaxReturnService.saveTaxReturn();
  }

  flashMessage(msg: string) {
    this.message = msg;
    setTimeout(() => this.message = '', 500);
  }
}
```

通过输入属性可以得到*要编辑的报税单*，这个属性被实现成了读取器（getter）和设置器（setter）。 设置器根据传进来的报税单初始化了组件自己的 `HeroTaxReturnService` 实例。 读取器总是返回该服务所存英雄的当前状态。 组件也会请求该服务来保存或还原这个报税单。

但如果该服务是一个全应用范围的单例就不行了。 每个组件就都会共享同一个服务实例，每个组件也都会覆盖属于其他英雄的报税单。

要防止这一点，我们就要在 `HeroTaxReturnComponent` 元数据的 `providers` 属性中配置组件级的注入器，来提供该服务。

```
// src/app/hero-tax-return.component.ts (providers)
providers: [ HeroTaxReturnService ]
```

`HeroTaxReturnComponent` 有它自己的 `HeroTaxReturnService` 提供商。 回忆一下，每个组件的*实例*都有它自己的注入器。 在组件级提供服务可以确保组件的*每个*实例都得到一个自己的、私有的服务实例，而报税单也不会再被意外覆盖了。

> 该场景代码中的其它部分依赖另一些 Angular 的特性和技术，你将会在本文档的其它章节学到。 你可以到[在线例子](https://www.angular.cn/generated/live-examples/hierarchical-dependency-injection/stackblitz.html) / [下载范例](https://www.angular.cn/generated/zips/hierarchical-dependency-injection/hierarchical-dependency-injection.zip)查看代码和下载它。

#### 场景: 专门的提供商

Another reason to re-provide a service at another level is to substitute a *more specialized* implementation of that service, deeper in the component tree.

考虑一个依赖于一系列服务的 Car 组件。 假设你在根注入器（代号 A）中配置了*通用的*提供商：`CarService`、`EngineService` 和 `TiresService`。

你创建了一个车辆组件（A），它显示一个从另外三个通用服务构造出的车辆。

然后，你创建一个子组件（B），它为 `CarService` 和 `EngineService` 定义了自己的*特殊的*提供商，它们具有更特殊的能力，适用于组件 B 的。

组件 B 是另一个组件 C 的父组件，而组件 C 又定义了自己的，*更特殊的*`CarService` 提供商。![car components](https://www.angular.cn/generated/images/guide/dependency-injection/car-components.png)

在幕后，每个组件都有自己的注入器，这个注入器带有为组件本身准备的 0 个、1 个或多个提供商。

当你在最深层的组件 C 解析 `Car` 的实例时，它使用注入器 C 解析生成了一个 `Car` 的实例，使用注入器 B 解析了 `Engine`，而 `Tires` 则是由根注入器 A 解析的。![car injector tree](https://www.angular.cn/generated/images/guide/dependency-injection/injector-tree.png)

> *车辆*场景下的代码位于 `car.components.ts` 和 `car.services.ts` 文件中，这个例子你可以在[在线例子](https://www.angular.cn/generated/live-examples/hierarchical-dependency-injection/stackblitz.html) / [下载范例](https://www.angular.cn/generated/zips/hierarchical-dependency-injection/hierarchical-dependency-injection.zip)查看和下载。

## DI 提供商

A dependency [provider](https://www.angular.cn/guide/glossary#provider) configures an injector with a [DI token](https://www.angular.cn/guide/glossary#di-token), which that injector uses to provide the concrete, runtime version of a dependency value. The injector relies on the provider configuration to create instances of the dependencies that it injects into components, directives, pipes, and other services.

You must configure an injector with a provider, or it won't know how to create the dependency.
 The most obvious way for an injector to create an instance of a service  class is with the class itself. If you specify the service class itself as the provider token, the  default behavior is for the injector to instantiate that class with `new`. 

In the following typical example, the `Logger` class itself provides a `Logger` instance. 

```
providers: [Logger]
```

You can, however, configure an injector with an alternative provider, in order to deliver some other object that provides the needed logging functionality. For instance:

- You can provide a substitute class.
- You can provide a logger-like object.
- Your provider can call a logger factory function.

### The `Provider` object literal

The class-provider syntax is a shorthand expression that expands into a provider configuration, defined by the [`Provider` interface](https://www.angular.cn/api/core/Provider). The following code snippets shows how a class that is given as the `providers` value is expanded into a full provider object.

```
providers: [Logger]
[{ provide: Logger, useClass: Logger }]
```

The expanded provider configuration is an object literal with two properties.

-  The `provide` property holds the [token](https://www.angular.cn/guide/dependency-injection#token) that serves as the key for both locating a dependency value and configuring the injector.
-   The second property is a provider definition object, which tells the injector how to create the dependency value. The provider-definition key can be `useClass`, as in the example. It can also be `useExisting`, `useValue`, or `useFactory`. Each of these keys provides a different type of dependency, as discussed below. 

### 替代类提供商

Different classes can provide the same service. For example, the following code tells the injector to return a `BetterLogger` instance when the component asks for a logger using the `Logger` token.

```
[{ provide: Logger, useClass: BetterLogger }]
```

#### 带依赖的类提供商

Another class, `EvenBetterLogger`, might display the user name in the log message. This logger gets the user from an injected `UserService` instance.

```
@Injectable()
export class EvenBetterLogger extends Logger {
  constructor(private userService: UserService) { super(); }

  log(message: string) {
    let name = this.userService.user.name;
    super.log(`Message to ${name}: ${message}`);
  }
}
```

The injector needs providers for both this new logging service and its dependent `UserService`. Configure this alternative logger with the `useClass` provider-definition key, like `BetterLogger`. The following array specifies both providers in the `providers` metadata option of the parent module or component.

```
[ UserService,
  { provide: Logger, useClass: EvenBetterLogger }]
```

#### 别名类提供商

假设老的组件依赖于 `OldLogger` 类。`OldLogger` 和 `NewLogger` 的接口相同，但是由于某种原因，我们没法修改老的组件来使用 `NewLogger`。

当老的组件要使用 `OldLogger` 记录信息时，你可能希望改用 `NewLogger` 的单例来处理它。 在这种情况下，无论某个组件请求老的 logger 还是新的 logger，依赖注入器都应该注入这个 `NewLogger` 的单例。 也就是说 `OldLogger` 应该是 `NewLogger` 的*别名*。

如果你试图用 `useClass` 为 `OldLogger` 指定一个别名 `NewLogger`，就会在应用中得到 `NewLogger` 的两个不同的实例。

```
[ NewLogger,
  // Not aliased! Creates two instances of `NewLogger`
  { provide: OldLogger, useClass: NewLogger}]
```

要确保只有一个 `NewLogger` 实例，就要用 `useExisting` 来为 `OldLogger` 指定别名。

```
[ NewLogger,
  // Alias OldLogger w/ reference to NewLogger
  { provide: OldLogger, useExisting: NewLogger}]
```

### 值提供商

有时候，提供一个现成的对象会比要求注入器从类去创建更简单一些。 如果要注入一个你已经创建过的对象，请使用 `useValue` 选项来配置该注入器。

下面的代码定义了一个变量，用来创建这样一个能扮演 logger 角色的对象。

```
// An object in the shape of the logger service
export function SilentLoggerFn() {}

const silentLogger = {
  logs: ['Silent logger says "Shhhhh!". Provided via "useValue"'],
  log: SilentLoggerFn
};
```

下面的提供商定义对象使用 `useValue` 作为 key 来把该变量与 `Logger` 令牌关联起来。

```
[{ provide: Logger, useValue: silentLogger }]
```


#### 非依赖类

并非所有的依赖都是类。有时候你会希望注入字符串、函数或对象。

```
// src/app/app.config.ts (excerpt)
export const HERO_DI_CONFIG: AppConfig = {
  apiEndpoint: 'api.heroes.com',
  title: 'Dependency Injection'
};
```

TypeScript 接口不是有效的令牌

`HERO_DI_CONFIG` 常量满足 `AppConfig` 接口的要求。 不幸的是，你不能用 TypeScript 的接口作为令牌。 在 TypeScript 中，接口是一个设计期的概念，无法用作 DI 框架在运行期所需的令牌。

```
// FAIL! Can't use interface as provider token
[{ provide: AppConfig, useValue: HERO_DI_CONFIG })]

// FAIL! Can't inject using the interface as the parameter type
constructor(private config: AppConfig){ }
```

> 如果你曾经在强类型语言中使用过依赖注入功能，这一点可能看起来有点奇怪，那些语言都优先使用接口作为查找依赖的 key。
> 不过，JavaScript 没有接口，所以，当 TypeScript 转译成 JavaScript 时，接口也就消失了。
> 在运行期间，没有留下任何可供 Angular 进行查找的接口类型信息。

替代方案之一是以类似于 `AppModule` 的方式，在 NgModule 中提供并注入这个配置对象。

```
// src/app/app.module.ts (providers)
providers: [
  UserService,
  { provide: APP_CONFIG, useValue: HERO_DI_CONFIG }
],
```

另一个为非类依赖选择提供商令牌的解决方案是定义并使用 `InjectionToken` 对象。

```
// src/app/app.config.ts
import { InjectionToken } from '@angular/core';
export const APP_CONFIG = new InjectionToken<AppConfig>('app.config');
```

The type parameter, while optional, conveys the dependency's type to developers and tooling. The token description is another developer aid.

使用 `InjectionToken` 对象注册依赖提供商：

```
providers: [{ provide: APP_CONFIG, useValue: HERO_DI_CONFIG }]
```

借助参数装饰器 `@Inject()`，你可以把这个配置对象注入到任何需要它的构造函数中。

```
constructor(@Inject(APP_CONFIG) config: AppConfig) {
  this.title = config.title;
}
```

> Although the `AppConfig` interface plays no role in dependency injection, it supports typing of the configuration object within the class. ???

### 工厂提供商

有时候你需要动态创建依赖值，创建时需要的信息你要等运行期间才能拿到。 比如，你可能需要某个在浏览器会话过程中会被反复修改的信息，而且这个可注入服务还不能独立访问这个信息的源头。

这种情况下，你可以使用*工厂提供商*。 当需要从第三方库创建依赖项实例时，工厂提供商也很有用，因为第三方库不是为 DI 而设计的。

比如，假设 `HeroService` 必须对普通用户隐藏*秘密*英雄，只有得到授权的用户才能看到他们。

像 `EvenBetterLogger` 一样，`HeroService` 需要知道该用户是否有权查看秘密英雄。 而认证信息可能会在应用的单个会话中发生变化，比如你改用另一个用户登录。

假设你不希望直接把 `UserService` 注入到 `HeroService` 中，因为你不希望把这个服务与那些高度敏感的信息牵扯到一起。 这样 `HeroService` 就无法直接访问到用户信息，来决定谁有权访问，谁没有。

要解决这个问题，我们给 `HeroService` 的构造函数一个逻辑型标志，以控制是否显示秘密英雄。

```
// src/app/heroes/hero.service.ts (excerpt)
constructor(
  private logger: Logger,
  private isAuthorized: boolean) { }

getHeroes() {
  let auth = this.isAuthorized ? 'authorized ' : 'unauthorized';
  this.logger.log(`Getting heroes for ${auth} user.`);
  return HEROES.filter(hero => this.isAuthorized || !hero.isSecret);
}
```

你可以注入 `Logger` 但是不能注入 `isAuthorized` 标志。不过你可以改用工厂提供商来为 `HeroService` 创建一个新的 logger 实例。

工厂提供商需要一个工厂函数。

```
// src/app/heroes/hero.service.provider.ts (excerpt)
let heroServiceFactory = (logger: Logger, userService: UserService) => {
  return new HeroService(logger, userService.user.isAuthorized);
};
```

虽然 `HeroService` 不能访问 `UserService`，但是工厂函数可以。你把 `Logger` 和 `UserService` 注入到了工厂提供商中，并让注入器把它们传给这个工厂函数。

```
// src/app/heroes/hero.service.provider.ts (excerpt)
export let heroServiceProvider =
  { provide: HeroService,
    useFactory: heroServiceFactory,
    deps: [Logger, UserService]
  };
```

- `useFactory` 字段告诉 Angular 该提供商是一个工厂函数，该函数的实现代码是 `heroServiceFactory`。 
-   `deps` 属性是一个[提供商令牌](https://www.angular.cn/guide/dependency-injection#token)数组。 `Logger` 和 `UserService` 类作为它们自己的类提供商令牌使用。 注入器解析这些令牌，并把与之对应的服务注入到相应的工厂函数参数表中。

注意，你把这个工厂提供商保存到了一个导出的变量 `heroServiceProvider` 中。 这个额外的步骤让工厂提供商可被复用。 你可以在任何需要它的地方用这个变量来配置 `HeroService` 的提供商。 在这个例子中，你只在 `HeroesComponent` 中用到了它。你在该组件元数据的 `providers` 数组中用 `heroServiceProvider` 替换了 `HeroService`。

```
import { Component }          from '@angular/core';
import { heroServiceProvider } from './hero.service.provider';

@Component({
  selector: 'app-heroes',
  providers: [ heroServiceProvider ],
  template: `
    <h2>Heroes</h2>
    <app-hero-list></app-hero-list>
  `
})
export class HeroesComponent { }
```

### 预定义令牌与多提供商

Angular 提供了一些内置的注入令牌常量，你可以用它们来自定义系统的多种行为。

比如，你可以使用下列内置令牌来切入 Angular 框架的启动和初始化过程。 提供商对象可以把任何一个注入令牌与一个或多个用来执行应用初始化操作的回调函数关联起来。

- [PLATFORM_INITIALIZER](https://www.angular.cn/api/core/PLATFORM_INITIALIZER)：平台初始化之后调用的回调函数。
- [APP_BOOTSTRAP_LISTENER](https://www.angular.cn/api/core/APP_BOOTSTRAP_LISTENER)：每个启动组件启动完成之后调用的回调函数。这个处理器函数会收到这个启动组件的 ComponentRef 实例。
- [APP_INITIALIZER](https://www.angular.cn/api/core/APP_INITIALIZER)：应用初始化之前调用的回调函数。注册的所有初始化器都可以（可选地）返回一个 Promise。所有返回 Promise 的初始化函数都必须在应用启动之前解析完。如果任何一个初始化器失败了，该应用就不会继续启动。

该提供商对象还有第三个选项 `multi: true`，把它和 `APP_INITIALIZER` 一起使用可以为特定的事件注册多个处理器。

比如，当启动应用时，你可以使用同一个令牌注册多个初始化器。???

```
export const APP_TOKENS = [
 { provide: PLATFORM_INITIALIZER, useFactory: platformInitialized, multi: true    },
 { provide: APP_INITIALIZER, useFactory: delayBootstrapping, multi: true },
 { provide: APP_BOOTSTRAP_LISTENER, useFactory: appBootstrapped, multi: true },
];
```

在其它地方，多个提供商也同样可以和单个令牌关联起来。 比如，你可以使用内置的 [NG_VALIDATORS](https://www.angular.cn/api/forms/NG_VALIDATORS) 令牌注册自定义表单验证器，还可以在提供商定义对象中使用 `multi: true` 属性来为指定的验证器令牌提供多个验证器实例。 Angular 会把你的自定义验证器添加到现有验证器的集合中。

路由器也同样用多个提供商关联到了一个令牌。 当你在单个模块中用 [RouterModule.forRoot](https://www.angular.cn/api/router/RouterModule#forroot) 和 [RouterModule.forChild](https://www.angular.cn/api/router/RouterModule#forchild) 提供了多组路由时，[ROUTES](https://www.angular.cn/api/router/ROUTES) 令牌会把这些不同的路由组都合并成一个单一值。

> 搜索 [API 文档中的常量](https://www.angular.cn/api?type=const)以了解更多内置令牌。

### 可摇树优化的提供商

摇树优化是指一个编译器选项，意思是把应用中未引用过的代码从最终生成的包中移除。
如果提供商是可摇树优化的，Angular 编译器就会从最终的输出内容中移除应用代码中从未用过的服务。这会显著减小你的打包体积。

> 由于还可能用 `injector.get(Service)` 的形式直接注入服务，所以 Angular 无法准确识别出代码中可能发生此注入的全部位置，为保险起见，只能把服务包含在注入器中。因此，在 NgModule 或 组件级别提供的服务是无法被摇树优化掉的。

下面这个不可摇树优化提供商的例子为 NgModule 注入器配置了一个服务提供商。

```
// src/app/tree-shaking/service-and-modules.ts
import { Injectable, NgModule } from '@angular/core';

@Injectable()
export class Service {
  doSomething(): void {
  }
}

@NgModule({
  providers: [Service],
})
export class ServiceModule {
}
```

该模块以后可以导入到你的应用模块中，以便该服务可注入到你的应用中，例子如下。

```
// src/app/tree-shaking/app.modules.ts
@NgModule({
  imports: [
    BrowserModule,
    RouterModule.forRoot([]),
    ServiceModule,
  ],
})
export class AppModule {
}
```

When `ngc` runs, it compiles `AppModule` into a module factory, which contains definitions for all the providers declared in all the modules it includes. At runtime, this factory becomes an injector that instantiates these services.

When `ngc` runs, it compiles `AppModule`  into a module factory, which contains definitions for all the providers  declared in all the modules it includes. At runtime, this factory  becomes an injector that instantiates these services.

Tree-shaking  doesn't work here because Angular can't decide to exclude one chunk of  code (the provider definition for the service within the module factory)  based on whether another chunk of code (the service class) is used. To  make services tree-shakable, the information about how to construct an  instance of the service (the provider definition) needs to be a part of  the service class itself. ???

#### 创建可摇树优化的提供商

只要在服务本身的 `@Injectable()` 装饰器中指定，而不是在依赖该服务的 NgModule 或组件的元数据中指定，你就可以制作一个可摇树优化的提供商。

下面的例子展示了与上面的 `ServiceModule` 例子等价的可摇树优化的版本。

```
// src/app/tree-shaking/service.ts
@Injectable({
  providedIn: 'root',
})
export class Service {
}
```

The service can be instantiated by configuring a factory function, as in the following example.

```
// src/app/tree-shaking/service.0.ts
@Injectable({
  providedIn: 'root',
  useFactory: () => new Service('dependency'),
})
export class Service {
  constructor(private dep: string) {
  }
}
```

> To override ??? a tree-shakable provider, configure the injector of a specific NgModule or component with another provider, using the `providers: []` array syntax of the `@NgModule()` or `@Component()` decorator.

## DI 实战

### 嵌套的服务依赖

有时候一个服务依赖其它服务...而其它服务可能依赖另外的更多服务。 依赖注入框架会负责正确的顺序解析这些嵌套的依赖项。 在每一步，依赖的使用者只要在它的构造函数里简单声明它需要什么，框架就会完成所有剩下的事情。

下面的例子往 `AppComponent` 里声明它依赖 `LoggerService` 和 `UserContext`。

```
// src/app/app.component.ts
constructor(logger: LoggerService, public userContext: UserContextService) {
  userContext.loadUser(this.userId);
  logger.logInfo('AppComponent initialized');
}
```

`UserContext` 转而依赖 `LoggerService` 和 `UserService`（这个服务用来收集特定用户信息）。

```
// user-context.service.ts (injection)
@Injectable({
  providedIn: 'root'
})
export class UserContextService {
  constructor(private userService: UserService, private loggerService: LoggerService) {
  }
}
```

当 Angular 新建 `AppComponent` 时，依赖注入框架会先创建一个 `LoggerService` 的实例，然后创建 `UserContextService` 实例。`UserContextService` 也需要框架刚刚创建的这个 `LoggerService` 实例，这样框架才能为它提供同一个实例。`UserContextService` 还需要框架创建过的 `UserService`。`UserService` 没有其它依赖，所以依赖注入框架可以直接 `new` 出该类的一个实例，并把它提供给 `UserContextService` 的构造函数。

### 把服务的范围限制到某个组件的子树下

An Angular application has multiple injectors, arranged in a tree hierarchy that parallels the component tree. Each injector creates a singleton instance of a dependency. That same instance is injected wherever that injector provides that service. A particular service can be provided and created at any level of the injector hierarchy, which means that there can be multiple instances of a service if it is provided by multiple injectors.

通过*在组件树的子级根组件*中提供服务，可以把一个被注入服务的作用域局限在应用程序结构中的某个*分支*中。 这个例子中展示了如何通过把服务添加到子组件 `@Component()` 装饰器的 `providers` 数组中，来为 `HeroesBaseComponent` 提供另一个 `HeroService` 实例：

```
// src/app/sorted-heroes.component.ts (HeroesBaseComponent excerpt)
@Component({
  selector: 'app-unsorted-heroes',
  template: `<div *ngFor="let hero of heroes">{{hero.name}}</div>`,
  providers: [HeroService]
})
export class HeroesBaseComponent implements OnInit {
  constructor(private heroService: HeroService) { }
}
```

当 Angular 新建 `HeroBaseComponent` 的时候，它会同时新建一个 `HeroService` 实例，该实例只在该组件及其子组件(如果有)中可见。

也可以在应用程序别处的另一个组件里提供 `HeroService`。这样就会导致在另一个注入器中存在该服务的另一个实例。

### 多个服务实例（沙箱式隔离）

在组件树的*同一个级别*上，有时需要一个服务的多个实例。

一个用来保存其伴生组件的实例状态的服务就是个好例子。 每个组件都需要该服务的单独实例。 每个服务有自己的工作状态，与其它组件的服务和状态隔离。这叫做**沙箱化**，因为每个服务和组件实例都在自己的沙箱里运行。

通过在自己的元数据(metadata)`providers` 数组里面列出 `HeroCacheService`, 这样每个`HeroBioComponent` 就能*拥有*自己独立的 `HeroCacheService` 实例了。

```
// src/app/hero-bio.component.ts
@Component({
  selector: 'app-hero-bio',
  template: `
    <h4>{{hero.name}}</h4>
    <ng-content></ng-content>
    <textarea cols="25" [(ngModel)]="hero.description"></textarea>`,
  providers: [HeroCacheService]
})

export class HeroBioComponent implements OnInit  {
  @Input() heroId: number;

  constructor(private heroCache: HeroCacheService) { }

  ngOnInit() { this.heroCache.fetchCachedHero(this.heroId); }

  get hero() { return this.heroCache.hero; }
}
```

父组件 `HeroBiosComponent` 把一个值绑定到 `heroId`。`ngOnInit` 把该 `id` 传递到服务，然后服务获取和缓存英雄。`hero` 属性的 getter 从服务里面获取缓存的英雄，并在模板里显示它绑定到属性值。

### 使用参数装饰器来限定依赖查找方式

通过在类的构造函数中对服务参数使用*参数装饰器*，可以提供一些选项来修改默认的搜索行为。

#### Make a dependency `@Optional` and limit search with `@Host`

某些情况下，你需要限制搜索，或容忍依赖项的缺失。 你可以使用组件构造函数参数上的 `@Host` 和 `@Optional` 这两个限定装饰器来修改 Angular 的搜索行为。

- `@Optional` 属性装饰器告诉 Angular 当找不到依赖时就返回 null。
-   `@Host` 属性装饰器会禁止在*宿主组件*以上的搜索。宿主组件通常就是请求该依赖的那个组件。 不过，当该组件投影进某个*父*组件时，那个父组件就会变成宿主。

#### 使用 [@Inject](https://www.angular.cn/api/core/Inject) 指定自定义提供商 ???

自定义提供商让你可以为隐式依赖提供一个具体的实现，比如内置浏览器 API。下面的例子使用 `InjectionToken` 来提供 [localStorage](https://developer.mozilla.org/en-US/docs/Web/API/Window/localStorage)，将其作为 `BrowserStorageService` 的依赖项。???

```
// src/app/storage.service.ts
import { Inject, Injectable, InjectionToken } from '@angular/core';

export const BROWSER_STORAGE = new InjectionToken<Storage>('Browser Storage', {
  providedIn: 'root',
  factory: () => localStorage
});

@Injectable({
  providedIn: 'root'
})
export class BrowserStorageService {
  constructor(@Inject(BROWSER_STORAGE) public storage: Storage) {}

  get(key: string) {
    this.storage.getItem(key);
  }

  set(key: string, value: string) {
    this.storage.setItem(key, value);
  }

  remove(key: string) {
    this.storage.removeItem(key);
  }

  clear() {
    this.storage.clear();
  }
}
```

`factory` 函数返回 window 对象上的 `localStorage` 属性。`Inject` 装饰器修饰一个构造函数参数，用于为某个依赖提供自定义提供商。现在，就可以在测试期间使用 `localStorage` 的 Mock API 来覆盖这个提供商了，而不必与真实的浏览器 API 进行交互。

#### 使用 [@Self](https://www.angular.cn/api/core/Self) 和 [@SkipSelf](https://www.angular.cn/api/core/SkipSelf) 来修改提供商的搜索方式 ???

Providers can also be scoped by injector through constructor parameter decorators. The following example overrides the `BROWSER_STORAGE` token in the `Component` class `providers` with the `sessionStorage` browser API. The same `BrowserStorageService` is injected twice in the constructor, decorated with `@Self` and `@SkipSelf` to define which injector handles the provider dependency.

```
// src/app/storage.component.ts
import { Component, OnInit, Self, SkipSelf } from '@angular/core';
import { BROWSER_STORAGE, BrowserStorageService } from './storage.service';

@Component({
  selector: 'app-storage',
  template: `
    Open the inspector to see the local/session storage keys:

    <h3>Session Storage</h3>
    <button (click)="setSession()">Set Session Storage</button>

    <h3>Local Storage</h3>
    <button (click)="setLocal()">Set Local Storage</button>
  `,
  providers: [
    BrowserStorageService,
    { provide: BROWSER_STORAGE, useFactory: () => sessionStorage }
  ]
})
export class StorageComponent implements OnInit {

  constructor(
    @Self() private sessionStorageService: BrowserStorageService,
    @SkipSelf() private localStorageService: BrowserStorageService,
  ) { }

  ngOnInit() {
  }

  setSession() {
    this.sessionStorageService.set('hero', 'Mr. Nice - Session');
  }

  setLocal() {
    this.localStorageService.set('hero', 'Mr. Nice - Local');
  }
}     
```

使用 `@Self` 装饰器时，注入器只在该组件的注入器中查找提供商。`@SkipSelf` 装饰器可以让你跳过局部注入器，并在注入器树中向上查找，以发现哪个提供商满足该依赖。 `sessionStorageService` 实例使用浏览器的 `sessionStorage` 来跟 `BrowserStorageService` 打交道，而 `localStorageService` 跳过了局部注入器，使用根注入器提供的 `BrowserStorageService`，它使用浏览器的 `localStorage` API。

#### Inject the component's DOM element

即便开发者极力避免，仍然会有很多视觉效果和第三方工具 (比如 jQuery) 需要访问 DOM。这会让你不得不访问组件所在的 DOM 元素。

To illustrate, here's a simplified version of `HighlightDirective` from the [Attribute Directives](https://www.angular.cn/guide/attribute-directives) page.

```
// src/app/highlight.directive.ts
import { Directive, ElementRef, HostListener, Input } from '@angular/core';

@Directive({
  selector: '[appHighlight]'
})
export class HighlightDirective {

  @Input('appHighlight') highlightColor: string;

  private el: HTMLElement;

  constructor(el: ElementRef) {
    this.el = el.nativeElement;
  }

  @HostListener('mouseenter') onMouseEnter() {
    this.highlight(this.highlightColor || 'cyan');
  }

  @HostListener('mouseleave') onMouseLeave() {
    this.highlight(null);
  }

  private highlight(color: string) {
    this.el.style.backgroundColor = color;
  }
}
```

当用户把鼠标移到 DOM 元素上时，指令将指令所在的元素的背景设置为一个高亮颜色。

Angular 把构造函数参数 `el` 设置为注入的 `ElementRef`，该 `ElementRef` 代表了宿主的 DOM 元素， 它的 `nativeElement` 属性把该 DOM 元素暴露给了指令。

下面的代码把指令的 `myHighlight` 属性(Attribute)填加到两个 `<div>` 标签里，一个没有赋值，一个赋值了颜色。

```
// src/app/app.component.html (highlight)
<div id="highlight"  class="di-component"  appHighlight>
  <h3>Hero Bios and Contacts</h3>
  <div appHighlight="yellow">
    <app-hero-bios-and-contacts></app-hero-bios-and-contacts>
  </div>
</div>
```

### 使用提供商来定义依赖

In order to get a service from a dependency injector, you have to give it a [token](https://www.angular.cn/guide/glossary#token). Angular usually handles this transaction by specifying a constructor parameter and its type. The parameter type serves as the injector lookup token. Angular passes this token to the injector and assigns the result to the parameter.

If the injector has already cached an instance of the service associated with the token, it provides that instance. If it doesn't, it needs to make one using the provider associated with the token.

> If the injector doesn't have a provider for a requested token, it delegates the request to its parent injector, where the process repeats until there are no more injectors. If the search fails, the injector throws an error—unless the request was [optional](https://www.angular.cn/guide/dependency-injection-in-action#optional).

#### 定义提供商

用于实例化类的默认方法不一定总适合用来创建依赖。你可以到[依赖提供商](https://www.angular.cn/guide/dependency-injection-providers)部分查看其它方法。

`HeroOfTheMonthComponent` 例子示范了一些替代方案，展示了为什么需要它们。 它看起来很简单：一些属性和一些由 logger 生成的日志。

   ![Hero of the month](https://www.angular.cn/generated/images/guide/dependency-injection-in-action/hero-of-month.png) 

它背后的代码定制了 DI 框架提供依赖项的方法和位置。 这个例子阐明了通过[*提供*对象字面量](https://www.angular.cn/guide/dependency-injection-providers#provide)来把对象的定义和 DI 令牌关联起来的另一种方式。

```
// hero-of-the-month.component.ts
import { Component, Inject } from '@angular/core';

import { DateLoggerService } from './date-logger.service';
import { Hero }              from './hero';
import { HeroService }       from './hero.service';
import { LoggerService }     from './logger.service';
import { MinimalLogger }     from './minimal-logger.service';
import { RUNNERS_UP,
         runnersUpFactory }  from './runners-up';

@Component({
  selector: 'app-hero-of-the-month',
  templateUrl: './hero-of-the-month.component.html',
  providers: [
    { provide: Hero,          useValue:    someHero },
    { provide: TITLE,         useValue:   'Hero of the Month' },
    { provide: HeroService,   useClass:    HeroService },
    { provide: LoggerService, useClass:    DateLoggerService },
    { provide: MinimalLogger, useExisting: LoggerService },
    { provide: RUNNERS_UP,    useFactory:  runnersUpFactory(2), deps: [Hero, HeroService] }
  ]
})
export class HeroOfTheMonthComponent {
  logs: string[] = [];

  constructor(
      logger: MinimalLogger,
      public heroOfTheMonth: Hero,
      @Inject(RUNNERS_UP) public runnersUp: string,
      @Inject(TITLE) public title: string)
  {
    this.logs = logger.logs;
    logger.logInfo('starting up');
  }
}
```

`providers` 数组展示了你可以如何使用其它的键来定义提供商：`useValue`、`useClass`、`useExisting` 或 `useFactory`。

##### 值提供商：`useValue`

`useValue` 键让你可以为 DI 令牌关联一个固定的值。 使用该技巧来进行*运行期常量设置*，比如网站的基础地址和功能标志等。 你也可以在单元测试中使用*值提供商*，来用一个 Mock 数据来代替一个生产环境下的数据服务。

`HeroOfTheMonthComponent` 例子中有两个**值-提供商**。

```
// dependency-injection-in-action/src/app/hero-of-the-month.component.ts
{ provide: Hero,          useValue:    someHero },
{ provide: TITLE,         useValue:   'Hero of the Month' },
```

-   第一处提供了用于 `Hero` 令牌的 `Hero` 类的现有实例，而不是要求注入器使用 `new` 来创建一个新实例或使用它自己的缓存实例。这里令牌就是这个类本身。
-   第二处为 `TITLE` 令牌指定了一个字符串字面量资源。 `TITLE` 提供商的令牌*不是一个类*，而是一个特别的提供商查询键，名叫[InjectionToken](https://www.angular.cn/guide/dependency-injection-in-action#injection-token)，表示一个 `InjectionToken` 实例。

你可以把 `InjectionToken` 用作任何类型的提供商的令牌，但是当依赖是简单类型（比如字符串、数字、函数）时，它会特别有用。

一个*值-提供商*的值必须在指定之前定义。其它类型的提供商都会*惰性创建*它们的值，也就是说只在需要注入它们的时候才创建。

##### 类提供商: useClass

`useClass` 提供的键让你可以创建并返回指定类的新实例。

你可以使用这类提供商来为公共类或默认类换上一个*替代实现*。比如，这个替代实现可以实现一种不同的策略来扩展默认类，或在测试环境中模拟真实类的行为。

```
// dependency-injection-in-action/src/app/hero-of-the-month.component.ts      
{ provide: HeroService,   useClass:    HeroService }, { provide: LoggerService, useClass:    DateLoggerService },     
```

第一个提供商是*展开了语法糖的*，是一个典型情况的展开。一般来说，被新建的类(`HeroService`)同时也是该提供商的注入令牌。 通常都选用缩写形式，完整形式可以让细节更明确。

第二个提供商使用 `DateLoggerService` 来满足 `LoggerService`。该 `LoggerService` 在 `AppComponent` 级别已经被注册。当*这个组件*要求 `LoggerService` 的时候，它得到的却是 `DateLoggerService` 服务的实例。

> 这个组件及其子组件会得到 `DateLoggerService` 实例。这个组件树之外的组件得到的仍是 `LoggerService` 实例。

#### 别名提供商：useExisting

`useExisting` 提供了一个键，让你可以把一个令牌映射成另一个令牌。实际上，第一个令牌就是第二个令牌所关联的服务的*别名*，这样就创建了访问同一个服务对象的两种途径。

```
// dependency-injection-in-action/src/app/hero-of-the-month.component.ts
{ provide: MinimalLogger, useExisting: LoggerService },
```

你可以使用别名接口来窄化 API。下面的例子中使用别名就是为了这个目的。

想象 `LoggerService` 有个很大的 API 接口，远超过现有的三个方法和一个属性。你可能希望把 API 接口收窄到只有两个你确实需要的成员。在这个例子中，`MinimalLogger`[*类-接口*](https://www.angular.cn/guide/dependency-injection-in-action#class-interface)，就将这个 API 成功缩小到了只有两个成员：???

```
// Class used as a "narrowing" interface that exposes a minimal logger
// Other members of the actual implementation are invisible
export abstract class MinimalLogger {
  logs: string[];
  logInfo: (msg: string) => void;
}
```

下面的例子在一个简化版的 `HeroOfTheMonthComponent` 中使用 `MinimalLogger`。

```
// src/app/hero-of-the-month.component.ts (minimal version)
@Component({
  selector: 'app-hero-of-the-month',
  templateUrl: './hero-of-the-month.component.html',
  // TODO: move this aliasing, `useExisting` provider to the AppModule
  providers: [{ provide: MinimalLogger, useExisting: LoggerService }]
})
export class HeroOfTheMonthComponent {
  logs: string[] = [];
  constructor(logger: MinimalLogger) {
    logger.logInfo('starting up');
  }
}
```

`HeroOfTheMonthComponent` 构造函数的 `logger` 参数是一个 `MinimalLogger` 类型，支持 TypeScript 的编辑器里，只能看到它的两个成员 `logs` 和 `logInfo`：

   ![MinimalLogger restricted API](https://www.angular.cn/generated/images/guide/dependency-injection-in-action/minimal-logger-intellisense.png) 

Behind the scenes, Angular sets the `logger` parameter to the full service registered under the `LoggingService` token, which happens to be the `DateLoggerService` instance that was [provided above](https://www.angular.cn/guide/dependency-injection-in-action#useclass).

##### 工厂提供商：useFactory

useFactory 提供了一个键，让你可以通过调用一个工厂函数来创建依赖实例，如下面的例子所示。

```
dependency-injection-in-action/src/app/hero-of-the-month.component.ts
{ provide: RUNNERS_UP,    useFactory:  runnersUpFactory(2), deps: [Hero, HeroService] }
```

注入器通过调用你用 `useFactory` 键指定的工厂函数来提供该依赖的值。 注意，提供商的这种形态还有第三个键 `deps`，它指定了供 `useFactory` 函数使用的那些依赖。

使用这项技术，可以用包含了一些**依赖服务和本地状态**输入的工厂函数来**建立一个依赖对象**。

这个依赖对象（由工厂函数返回的）通常是一个类实例，不过也可以是任何其它东西。 在这个例子中，依赖对象是一个表示 "月度英雄" 参赛者名称的字符串。

在这个例子中，局部状态是数字 `2`，也就是组件应该显示的参赛者数量。 该状态的值传给了 `runnersUpFactory()` 作为参数。 `runnersUpFactory()` 返回了*提供商的工厂函数*，它可以使用传入的状态值和注入的服务 `Hero` 和 `HeroService`。

```
// runners-up.ts (excerpt)
export function runnersUpFactory(take: number) {
  return (winner: Hero, heroService: HeroService): string => {
    /* ... */
  };
};
```

The provider factory function (returned by `runnersUpFactory()`) returns the actual dependency object, the string of names.

- The function takes a winning `Hero` and a `HeroService` as arguments.

Angular supplies these arguments from injected values identified by the two *tokens* in the `deps` array.

-  The function returns the string of names, which Angular than injects into the `runnersUp` parameter of `HeroOfTheMonthComponent`.

> The function retrieves candidate heroes from the `HeroService`, takes `2` of them to be the runners-up, and returns their concatenated names. Look at the [在线例子](https://www.angular.cn/generated/live-examples/dependency-injection-in-action/stackblitz.html) / [下载范例](https://www.angular.cn/generated/zips/dependency-injection-in-action/dependency-injection-in-action.zip) for the full source code.

### 提供替代令牌：类接口与 'InjectionToken'

Angular dependency injection is easiest when the provider token is a class that is also the type of the returned dependency object, or service. 但令牌不一定都是类，就算它是一个类，它也不一定都返回类型相同的对象。

#### Classinterface

```
// dependency-injection-in-action/src/app/hero-of-the-month.component.ts
{ provide: MinimalLogger, useExisting: LoggerService },
```

该 `MinimalLogger` 是一个抽象类。

```
// dependency-injection-in-action/src/app/minimal-logger.service.ts
// Class used as a "narrowing" interface that exposes a minimal logger
// Other members of the actual implementation are invisible
export abstract class MinimalLogger {
  logs: string[];
  logInfo: (msg: string) => void;
}
```

An abstract class is usually a base class that you can extend. In this app, however there is no class that inherits from `MinimalLogger`.

The `LoggerService` and the `DateLoggerService`could have inherited from `MinimalLogger`, or they could have implemented it instead, in the manner of an interface. But they did neither. `MinimalLogger` is used only as a dependency injection token.

When you use a class this way, it's called a *class interface*.

As mentioned in [DI Providers](https://www.angular.cn/guide/dependency-injection-providers#interface-not-valid-token),  an interface is not a valid DI token because it is a TypeScript  artifact that doesn't exist at run time. Use this abstract class  interface to get the strong typing of an interface, and also use it as a  provider token in the way you would a normal class.

A  class interface should define *only* the members that its consumers are allowed to call. Such a narrowing interface helps decouple the concrete class from its consumers.

> Using a class as an interface gives you the characteristics of an interface in a real JavaScript object. To minimize memory cost, however, the class should have *no implementation*. The `MinimalLogger` transpiles to this unoptimized, pre-minified JavaScript for a constructor function.
>
> ```
> // dependency-injection-in-action/src/app/minimal-logger.service.ts 
> var MinimalLogger = (function () { // ???
>   function MinimalLogger() {}
>   return MinimalLogger;
> }());
> exports("MinimalLogger", MinimalLogger);   
> ```
>
> Notice that it doesn't have any members. It never grows no matter how many members you add to the class, as long as those members are typed but not implemented. Look again at the TypeScript `MinimalLogger` class to confirm that it has no implementation.

#### 'InjectionToken' 对象

依赖对象可以是一个简单的值，比如日期，数字和字符串，或者一个无形的对象，比如数组和函数。

Such objects don't have application interfaces and therefore aren't well represented by a class. They're better represented by a token that is both unique and symbolic, a JavaScript object that has a friendly name but won't conflict with another token that happens to have the same name. 

`InjectionToken` 具有这些特征。在*Hero of the Month*例子中遇见它们两次，一个是 *title* 的值，一个是 *runnersUp* 工厂提供商。

```
// dependency-injection-in-action/src/app/hero-of-the-month.component.ts
{ provide: TITLE,         useValue:   'Hero of the Month' },
{ provide: RUNNERS_UP,    useFactory:  runnersUpFactory(2), deps: [Hero, HeroService] }
```

这样创建 `TITLE` 令牌：

```
// dependency-injection-in-action/src/app/hero-of-the-month.component.ts
import { InjectionToken } from '@angular/core';

export const TITLE = new InjectionToken<string>('title');
```

The type parameter, while optional, conveys the dependency's type to developers and tooling.
The token description is another developer aid.

### 注入到派生类

当编写一个继承自另一个组件的组件时，要格外小心。如果基础组件有依赖注入，必须要在派生类中重新提供和重新注入它们，并将它们通过构造函数传给基类。

```
// src/app/sorted-heroes.component.ts (HeroesBaseComponent)
@Component({
  selector: 'app-unsorted-heroes',
  template: `<div *ngFor="let hero of heroes">{{hero.name}}</div>`,
  providers: [HeroService]
})
export class HeroesBaseComponent implements OnInit {
  constructor(private heroService: HeroService) { }

  heroes: Array<Hero>;

  ngOnInit() {
    this.heroes = this.heroService.getAllHeroes();
    this.afterGetHeroes();
  }

  // Post-process heroes in derived class override.
  protected afterGetHeroes() {}

}
```

```
// src/app/sorted-heroes.component.ts (SortedHeroesComponent)
@Component({
  selector: 'app-sorted-heroes',
  template: `<div *ngFor="let hero of heroes">{{hero.name}}</div>`,
  providers: [HeroService]
})
export class SortedHeroesComponent extends HeroesBaseComponent {
  constructor(heroService: HeroService) {
    super(heroService);
  }

  protected afterGetHeroes() {
    this.heroes = this.heroes.sort((h1, h2) => {
      return h1.name < h2.name ? -1 :
            (h1.name > h2.name ? 1 : 0);
    });
  }
}
```

现在，请注意 `afterGetHeroes()` 方法。 你的第一反应是在 `SortedHeroesComponent` 组件里面建一个 `ngOnInit` 方法来做排序。但是 Angular 会先调用*派生*类的 `ngOnInit`，后调用基类的 `ngOnInit`， 所以可能在*英雄到达之前*就开始排序。这就产生了一个讨厌的错误。

覆盖基类的 `afterGetHeroes()` 方法可以解决这个问题。

These complications argue for **avoiding component inheritance**

### 使用一个前向引用(*forwardRef*)来打破循环 

在 TypeScript 里面，类声明的顺序是很重要的。如果一个类尚未定义，就不能引用它。

这通常不是一个问题，特别是当你遵循*一个文件一个类*规则的时候。 但是有时候循环引用可能不能避免。当一个类*A 引用类 B*，同时'B'引用'A'的时候，你就陷入困境了：它们中间的某一个必须要先定义。

Angular 的 `forwardRef()` 函数建立一个*间接地*引用，Angular 可以随后解析。

这个关于*父查找器*的例子中全都是没办法打破的循环类引用。

当一个类*需要引用自身*的时候，你面临同样的困境，就像在 `AlexComponent` 的 `provdiers` 数组中遇到的困境一样。 该 `providers` 数组是一个 `@Component()` 装饰器函数的一个属性，它必须在类定义*之前*出现。

使用 `forwardRef` 来打破这种循环：???

```
// parent-finder.component.ts (AlexComponent providers)
providers: [{ provide: Parent, useExisting: forwardRef(() => AlexComponent) }],
```

## 浏览组件树

应用的组件之间经常需要共享信息。你通常要用松耦合的技术来共享信息，比如数据绑定???和服务共享。但是有时候让一个组件直接引用另一个组件还是很有意义的。 例如，你需要通过另一个组件的直接引用来访问其属性或调用其方法。

在 Angular 中获取组件引用略微有些棘手。 Angular 组件本身并没有一棵可以用编程方式检查或浏览的树。 其父子关系是通过组件的[视图对象](https://www.angular.cn/guide/glossary#view)间接建立的。

每个组件都有一棵以该组件的宿主视图为根节点的[视图树](https://www.angular.cn/guide/glossary#view-hierarchy)。

有一些用于在视图树中*向下*导航的 API。 请到 [API 参考手册](https://www.angular.cn/api/)中查看 `Query`、`QueryList`、`ViewChildren` 和 `ContentChildren`。

不存在用于获取父引用的公共 API。 不过，由于每个组件的实例都会添加到注入器的容器中，因此你可以通过 Angular 的依赖注入来访问父组件。

### 查找已知类型的父组件

You use standard class injection to acquire a parent component whose type you know.

在下面的例子中，父组件 `AlexComponent` 具有一些子组件，包括 `CathyComponent`。

```
// parent-finder.component.ts (AlexComponent v.1)
@Component({
  selector: 'alex',
  template: `
    <div class="a">
      <h3>{{name}}</h3>
      <cathy></cathy>
      <craig></craig>
      <carol></carol>
    </div>`,
})
export class AlexComponent extends Base
{
  name = 'Alex';
}
```

**Cathy** reports whether or not she has access to **Alex** after injecting an `AlexComponent` into her constructor:

```
// parent-finder.component.ts (CathyComponent)
@Component({
  selector: 'cathy',
  template: `
  <div class="c">
    <h3>Cathy</h3>
    {{alex ? 'Found' : 'Did not find'}} Alex via the component class.<br>
  </div>`
})
export class CathyComponent {
  constructor( @Optional() public alex: AlexComponent ) { }
}
```

### Unable to find a parent by its base class

 Alex 组件*扩展*（*继承*）了基类 

```
// parent-finder.component.ts (Alex class signature)
export class AlexComponent extends Base
```

`CraigComponent` 试图把 `Base` 注入到它的构造函数参数 `alex` 中，并汇报这次注入是否成功了。

```
// parent-finder.component.ts (CraigComponent)
@Component({
  selector: 'craig',
  template: `
  <div class="c">
    <h3>Craig</h3>
    {{alex ? 'Found' : 'Did not find'}} Alex via the base class.
  </div>`
})
export class CraigComponent {
  constructor( @Optional() public alex: Base ) { }
}
```

[在线例子](https://www.angular.cn/generated/live-examples/dependency-injection-in-action/stackblitz.html) / [下载范例](https://www.angular.cn/generated/zips/dependency-injection-in-action/dependency-injection-in-action.zip) 确认了 `alex` 参数为空。**你不能通过父组件的基类注入它**。

### Find a parent by its class interface

You can find a parent component with a [class interface](https://www.angular.cn/guide/dependency-injection-in-action#class-interface). The parent must cooperate by providing an *alias* to itself in the name of a class interface token.

编写一个 [*别名提供商*](https://www.angular.cn/guide/dependency-injection-in-action#useexisting)（一个 `provide` 对象字面量，其中有一个 `useExisting` 定义），创造了另一种方式来注入同一个组件实例，并把那个提供商添加到 `AlexComponent` `@Component()` 元数据的 `providers` 数组中。

```
// parent-finder.component.ts (AlexComponent providers)
providers: [{ provide: Parent, useExisting: forwardRef(() => AlexComponent) }],
```

[Parent](https://www.angular.cn/guide/dependency-injection-navtree#parent-token) 是该提供商的类接口。 [*forwardRef*](https://www.angular.cn/guide/dependency-injection-in-action#forwardref) 用于打破循环引用，因为在你刚才这个定义中 `AlexComponent` 引用了自身。

*Alex* 的第三个子组件 *Carol*，把其父组件注入到了自己的 `parent` 参数中 —— 和你以前做过的一样。

```
// parent-finder.component.ts (CarolComponent class)
export class CarolComponent {
  name = 'Carol';
  constructor( @Optional() public parent: Parent ) { }
}
```

![Alex in action](https://www.angular.cn/generated/images/guide/dependency-injection-in-action/alex.png)???

### 使用@SkipSelf()在树中查找父组件

想象一下组件树的一个分支：*Alice* -> *Barry* -> *Carol*。无论 *Alice* 还是 *Barry* 都实现了类接口 `Parent` 。

*Barry* is the problem. He needs to reach his parent, *Alice*, and also be a parent to *Carol*. That means he must both *inject* the `Parent` class interface to get *Alice* and *provide* a `Parent` to satisfy *Carol*.

*Barry* 的代码如下。

```
// parent-finder.component.ts (BarryComponent)
const templateB = `
  <div class="b">
    <div>
      <h3>{{name}}</h3>
      <p>My parent is {{parent?.name}}</p>
    </div>
    <carol></carol>
    <chris></chris>
  </div>`;

@Component({
  selector:   'barry',
  template:   templateB,
  providers:  [{ provide: Parent, useExisting: forwardRef(() => BarryComponent) }]
})
export class BarryComponent implements Parent {
  name = 'Barry';
  constructor( @SkipSelf() @Optional() public parent: Parent ) { }
}
```

现在，注意看 *Barry* 的构造函数。

```
// Barry's constructor
constructor( @SkipSelf() @Optional() public parent: Parent ) { }

// Carol's constructor
constructor( @Optional() public parent: Parent ) { }
```

`@SkipSelf` is essential for two reasons:

1.    它告诉注入器开始从组件树中*高于*自己的位置（也就是父组件）开始搜索 `Parent` 依赖。

2.  如果你省略了 `@SkipSelf` 装饰器，Angular 就会抛出循环依赖错误。

   `Cannot instantiate cyclic dependency! (BethComponent -> Parent -> BethComponent)`

### 父类接口

You [learned earlier](https://www.angular.cn/guide/dependency-injection-in-action#class-interface) that a class interface is an abstract class used as an interface rather than as a base class.

下面的例子定义了一个类接口 `Parent`。

```
// parent-finder.component.ts (Parent class-interface)
export abstract class Parent { name: string; }
```

`Parent` 类接口定义了一个带类型的 `name` 属性，但没有实现它。 这个 `name` 属性是父组件中唯一可供子组件调用的成员。 这样的窄化接口帮助把子组件从它的父组件中解耦出来。

一个组件想要作为父组件使用，就*应该*像 `AliceComponent` 那样实现这个类接口。

```
// parent-finder.component.ts (AliceComponent class signature)
export class AliceComponent implements Parent
```

这样做可以增加代码的清晰度，但在技术上并不是必要的。虽然 `AlexComponent` 像 `Base` 类所要求的一样具有 `name` 属性，但它的类签名中并没有提及 `Parent`。

```
// parent-finder.component.ts (AlexComponent class signature)
export class AlexComponent extends Base
```

> `AlexComponent` *应该*实现 `Parent` 才是一种正确的风格。这个例子中之所以没这样做，*只是*为了证明即使没有声明接口，代码也可以编译和运行。

### `provideParent()` 辅助函数

Writing variations of the same parent *alias provider* gets old quickly, especially this awful mouthful with a [*forwardRef*](https://www.angular.cn/guide/dependency-injection-in-action#forwardref).

```
// dependency-injection-in-action/src/app/parent-finder.component.ts
providers: [{ provide: Parent, useExisting: forwardRef(() => AlexComponent) }],
```

You can extract that logic into a helper function like the following.

```
// dependency-injection-in-action/src/app/parent-finder.component.ts
// Helper method to provide the current component instance in the name of a `parentType`.
const provideParent =
  (component: any) => {
    return { provide: Parent, useExisting: forwardRef(() => component) };
  };
```

现在，你可以为组件添加一个更简单、更有意义的父组件提供商。

```
// dependency-injection-in-action/src/app/parent-finder.component.ts
providers:  [ provideParent(AliceComponent) ]
```

一个修订后的版本，它默认为 `parent`，但是也能接受另一个父类接口作为可选的第二参数。

```
// dependency-injection-in-action/src/app/parent-finder.component.ts
// Helper method to provide the current component instance in the name of a `parentType`.
// The `parentType` defaults to `Parent` when omitting the second parameter.
const provideParent =
  (component: any, parentType?: any) => {
    return { provide: parentType || Parent, useExisting: forwardRef(() => component) };
  }; // ???
```

下面是针对不同父组件类型的用法。

```
// dependency-injection-in-action/src/app/parent-finder.component.ts
providers:  [ provideParent(BethComponent, DifferentParent) ]
```
