# Angular上手

#### Prerequisites

Node.js & npm package manager

#### 安装Angular CLI

```
npm install -g @angular/cli
```

#### 创建工作空间

```
ng new APP-NAME
```

#### 启动开发服务器

```
cd my-app
ng serve --open(或只用-o)
```

#### 创建新组件

```
ng generate component COMPONENT-NAME
```

#### 双向绑定

```
<input [(ngModel)]="hero.name" placeholder="name">
```

#### 导入模块

app.module.ts文件 

import { [FormsModule](https://www.angular.cn/api/forms/FormsModule) } from '@angular/forms';

imports: [
  BrowserModule,
  FormsModule
],

每个组件都必须声明在（且只能声明在）一个 [NgModule](https://www.angular.cn/guide/ngmodules) 中。

#### 事件绑定

```
<li *ngFor="let hero of heroes" (click)="onSelect(hero)">
```

#### ngIf

 `selectedHero` 为 `undefined` 时，`ngIf` 从 DOM 中移除了英雄详情

```
<div *ngIf="selectedHero"></div>
```

#### CSS类绑定

```
[class.selected]="hero === selectedHero"
```

如果当前行的英雄和 `selectedHero` 相同，Angular 就会添加 CSS 类 `selected`

#### 单向数据绑定

```
<app-hero-detail [hero]="selectedHero"></app-hero-detail>
```

#### 服务

创建服务

```
ng generate service hero
```

注入服务

```
constructor(private heroService: HeroService) { }
```

#### Observable

```typescript
import { Observable, of } from 'rxjs';

//返回数据
//------------
getHeroes(): Observable<Hero[]> {
  return of(HEROES);
}

//订阅
//------------
getHeroes(): void {
  this.heroService.getHeroes()
      .subscribe(heroes => this.heroes = heroes);
}
```

### Routing

#### 添加AppRoutingModule

AppRoutingModule是一个独立的顶级模块，负责加载和配置the router。它专注于路由功能，由根模块AppModule导入. By convention, the module class name is `AppRoutingModule` and it belongs in the `app-routing.module.ts` in the `src/app` folder.

生成

```
ng generate module app-routing --flat --module=app
```

> `--flat` 把这个文件放进了 `src/app` 中，而不是单独的目录中。
> `--module=app` 告诉 CLI 把它注册到 `AppModule` 的 `imports` 数组中。

#### 添加routes

```typescript
import { HeroesComponent }      from './heroes/heroes.component';

const routes: Routes = [
  { path: '', redirectTo: '/dashboard', pathMatch: 'full' },
  { path: 'dashboard', component: DashboardComponent },
  { path: 'detail/:id', component: HeroDetailComponent },
  { path: 'heroes', component: HeroesComponent }
];
```

#### RouterModule.forRoot()

你必须首先初始化路由器，并让它开始监听浏览器中的地址变化。

把 `RouterModule` 添加到 `@NgModule.imports` 数组中，并用 `routes` 来配置它。你只要调用 `imports` 数组中的 `RouterModule.forRoot()` 函数就行了。

```typescript
imports: [ RouterModule.forRoot(routes) ],
```

>这个方法之所以叫 `forRoot()`，是因为你要在应用的顶级配置这个路由器。
>`forRoot()` 方法会提供路由所需的服务提供商和指令，还会基于浏览器的当前 URL 执行首次导航。

#### 添加路由出口

`<router-outlet>` 会告诉路由器要在哪里显示路由到的视图。

```html
<h1>{{title}}</h1>
<router-outlet></router-outlet>
<app-messages></app-messages>
```

> 能在 `AppComponent` 中使用 `RouterOutlet`，是因为 `AppModule` 导入了 `AppRoutingModule`，而 `AppRoutingModule` 中导出了 `RouterModule`。

#### 添加路由链接

```html
<nav>
  <a routerLink="/heroes">Heroes</a>
</nav>
```

`routerLink` 是 [`RouterLink` 指令](https://www.angular.cn/tutorial/toh-pt5#routerlink)的选择器，它会把用户的点击转换为路由器的导航操作。
它是 `RouterModule` 中公开的另一个指令。

#### 添加默认路由

```typescript
{ path: '', redirectTo: '/dashboard', pathMatch: 'full' },
```

#### 占位符

```typescript
{ path: 'detail/:id', component: HeroDetailComponent },
```

`path` 中的冒号（`:`）表示 `:id` 是一个占位符，它表示某个特定英雄的 `id`。

#### 让组件支持路由

````typescript
import { ActivatedRoute } from '@angular/router';
import { Location } from '@angular/common';

import { HeroService }  from '../hero.service';

// 构造函数
constructor(
  private route: ActivatedRoute,
  private heroService: HeroService,
  private location: Location
) {}
````

[`ActivatedRoute`](https://www.angular.cn/api/router/ActivatedRoute) 保存着到这个 `HeroDetailComponent` 实例的路由信息。 这个组件对从 URL 中提取的路由参数感兴趣。 其中的 *id* 参数就是要显示的英雄的 `id`。

[`HeroService`](https://www.angular.cn/tutorial/toh-pt4) 从远端服务器获取英雄数据，本组件将使用它来获取*要显示的英雄*。

[`location`](https://www.angular.cn/api/common/Location) 是一个 Angular 的服务，用来与浏览器打交道。 [稍后](https://www.angular.cn/tutorial/toh-pt5#goback)，你就会使用它来导航回上一个视图。

#### 从route parameter提取参数

```typescript
ngOnInit(): void {
  this.getHero();
}

getHero(): void {
  const id = +this.route.snapshot.paramMap.get('id');
  this.heroService.getHero(id)
    .subscribe(hero => this.hero = hero);
}
```

`route.snapshot` 是一个路由信息的静态快照，抓取自组件刚刚创建完毕之后。

`paramMap` 是一个从 URL 中提取的路由参数值的字典。 `"id"` 对应的值就是要获取的英雄的 `id`。

路由参数总会是字符串。 JavaScript 的 (+) 操作符会把字符串转换成数字，英雄的 `id` 就是数字类型。

#### 服务中添加对应方法

```typescript
getHero(id: number): Observable<Hero> {
  // TODO: send the message _after_ fetching the hero
  this.messageService.add(`HeroService: fetched hero id=${id}`);
  return of(HEROES.find(hero => hero.id === id));
}
```

> 注意，反引号 ( ` ) 用于定义 JavaScript 的 [模板字符串字面量](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Template_literals)，以便嵌入 `id`。

#### 返回(Find the way back)

```
<button (click)="goBack()">go back</button>
```

```typescript
goBack(): void {
  this.location.back();
}
```

### HTTP

#### 安装内存Web API包

```
npm install angular-in-memory-web-api --save
```

> 该命令要在工程目录下执行