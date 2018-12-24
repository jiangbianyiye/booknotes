# Angular 上手

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

#### 启用HTTP服务

```
import { HttpClientModule }    from '@angular/common/http';
```

#### 模拟数据服务器

与使用[内存 Web API（*In-memory Web API*）](https://github.com/angular/in-memory-web-api)模拟出的远程服务器通讯

##### 安装内存Web API包

```
npm install angular-in-memory-web-api --save
```

> 该命令要在工程目录下执行

##### 导入`HttpClientInMemoryWebApiModule`

```
import { HttpClientInMemoryWebApiModule } from 'angular-in-memory-web-api';
import { InMemoryDataService }  from './in-memory-data.service';
```

#### 添加到 `@NgModule.imports` 数组中并配置

```
HttpClientModule,

// The HttpClientInMemoryWebApiModule module intercepts HTTP requests
// and returns simulated server responses.
// Remove it when a real server is ready to receive requests.
HttpClientInMemoryWebApiModule.forRoot(
  InMemoryDataService, { dataEncapsulation: false }
)
```

`forRoot()` 配置方法接受一个 `InMemoryDataService` 类（初期的内存数据库）作为参数

##### `in-memory-data.service.ts`示例

```
import { InMemoryDbService } from 'angular-in-memory-web-api';
import { Hero } from './hero';

export class InMemoryDataService implements InMemoryDbService {
  createDb() {
    const heroes = [
      { id: 11, name: 'Mr. Nice' },
      { id: 12, name: 'Narco' },
      { id: 13, name: 'Bombasto' },
      { id: 14, name: 'Celeritas' },
      { id: 15, name: 'Magneta' },
      { id: 16, name: 'RubberMan' },
      { id: 17, name: 'Dynama' },
      { id: 18, name: 'Dr IQ' },
      { id: 19, name: 'Magma' },
      { id: 20, name: 'Tornado' }
    ];
    return {heroes};
  }

  // Overrides the genId method to ensure that a hero always has an id.
  // If the heroes array is empty,
  // the method below returns the initial number (11).
  // if the heroes array is not empty, the method below returns the highest
  // hero id + 1.
  genId(heroes: Hero[]): number {
    return heroes.length > 0 ? Math.max(...heroes.map(hero => hero.id)) + 1 : 11;
  }
}
```

#### Http开发示例

##### 导入符号, 注入HttpClient

```
// 导入HTTP符号
import { HttpClient, HttpHeaders } from '@angular/common/http';

// 把 HttpClient 注入到构造函数中一个名叫 http 的私有属性中。
constructor(
  private http: HttpClient,
  private messageService: MessageService) { }
```

##### 包装MessageService的注入

```
/** Log a HeroService message with the MessageService */
private log(message: string) {
  this.messageService.add(`HeroService: ${message}`);
}
```

##### 定义资源访问地址(形式为`:base/:collectionName`)

base是要请求的资源, 而collectionName是in-memory-data-service.ts中的英雄数据对象

```
private heroesUrl = 'api/heroes';  // URL to web api
```

##### 通过 HttpClient 获取英雄

```
/** GET heroes from the server */
getHeroes (): Observable<Hero[]> {
  return this.http.get<Hero[]>(this.heroesUrl)
}
```

>`Observable` *可以*在一段时间内返回多个值。
>但来自 `HttpClient` 的 `Observable` 总是发出一个值，然后结束，再也不会发出其它值。

>`HttpClient.get` 默认情况下把响应体当做无类型的 JSON 对象进行返回。
>如果指定了可选的模板类型 `<Hero[]>`，就会给返回你一个类型化的对象。

##### 从Observable中取数据 ???

其它 API 可能在返回对象中深埋着你想要的数据。你可能要借助 RxJS 的 `map` 操作符对 `Observable` 的结果进行处理，以便把这些数据挖掘出来。

```
  /** GET hero by id. Return `undefined` when id not found */
  getHeroNo404<Data>(id: number): Observable<Hero> {
    const url = `${this.heroesUrl}/?id=${id}`;
    return this.http.get<Hero[]>(url)
      .pipe(
        map(heroes => heroes[0]), // returns a {0|1} element array
        tap(h => {
          const outcome = h ? `fetched` : `did not find`;
          this.log(`${outcome} hero id=${id}`);
        }),
        catchError(this.handleError<Hero>(`getHero id=${id}`))
      );
  }
```

#### 错误处理

导入 catchError 符号

```
import { catchError, map, tap } from 'rxjs/operators';
```

使用 `.pipe()` 方法来扩展 `Observable` 的结果，并给它一个 `catchError()` 操作符

```
getHeroes (): Observable<Hero[]> {
  return this.http.get<Hero[]>(this.heroesUrl)
    .pipe(
      catchError(this.handleError('getHeroes', []))
    );
}
```

`catchError()` 操作符会拦截失败的 Observable。它把错误对象传给*错误处理器*，*错误处理器*会处理这个错误。

##### handleError

 以下`handleError()` 方法会报告这个错误，并返回一个无害的结果（安全值），以便应用能正常工作。

以下 `handleError()` 将会在很多 `HeroService` 的方法之间共享，所以要把它通用化，以支持这些彼此不同的需求。

它不再直接处理这些错误，而是返回给 `catchError` 返回一个*错误处理*函数。还要用操作名和出错时要返回的安全值来对这个错误处理函数进行配置。

```
/**
 * Handle Http operation that failed.
 * Let the app continue.
 * @param operation - name of the operation that failed
 * @param result - optional value to return as the observable result
 */
private handleError<T> (operation = 'operation', result?: T) {
  return (error: any): Observable<T> => {

    // TODO: send the error to remote logging infrastructure
    console.error(error); // log to console instead

    // TODO: better job of transforming error for user consumption
    this.log(`${operation} failed: ${error.message}`);

    // Let the app keep running by returning an empty result.
    return of(result as T);
  };
}
```

#### 窥探(Tap into) Observable

使用 RxJS 的 `tap` 操作符会*查看* Observable 中的值，使用那些值做一些事情，并且把它们传出来。
这种 `tap` 回调不会改变这些值本身。

```
/** GET heroes from the server */
getHeroes (): Observable<Hero[]> {
  return this.http.get<Hero[]>(this.heroesUrl)
    .pipe(
      tap(heroes => this.log('fetched heroes')),
      catchError(this.handleError('getHeroes', []))
    );
}
```

#### 通过 id 获取英雄

大多数的 Web API 都支持以 `:baseURL/:id` 的形式根据 id 进行获取。

```typescript
/** GET hero by id. Will 404 if id not found */
getHero(id: number): Observable<Hero> {
  const url = `${this.heroesUrl}/${id}`;
  return this.http.get<Hero>(url).pipe(
    tap(_ => this.log(`fetched hero id=${id}`)),
    catchError(this.handleError<Hero>(`getHero id=${id}`))
  );
}
```

#### 修改英雄

添加一个保存按钮(该模块的html文件)

```
<button (click)="save()">save</button>
```

使用英雄服务中的 updateHero() 方法来保存对英雄名字的修改，然后导航回前一个视图。(该模块的ts类文件)

```typescript
save(): void {
   this.heroService.updateHero(this.hero)
     .subscribe(() => this.goBack());
 }
```

使用 http.put() 来把修改后的英雄保存到服务器上。(service 类文件)

```typescript
 /** PUT: update the hero on the server */
updateHero (hero: Hero): Observable<any> {
  return this.http.put(this.heroesUrl, hero, httpOptions).pipe(
    tap(_ => this.log(`updated hero id=${hero.id}`)),
    catchError(this.handleError<any>('updateHero'))
  );
}
```

#### 添加新英雄

使用一个和添加按钮成对的 `input` 元素.

```
<div>
  <label>Hero name:
    <input #heroName />
  </label>
  <!-- (click) passes input value to add() and then clears the input -->
  <button (click)="add(heroName.value); heroName.value=''">
    add
  </button>
</div>
```

点击事件触发时，调用组件的点击处理器，然后清空这个输入框

```typescript
add(name: string): void {
  name = name.trim();
  if (!name) { return; }
  this.heroService.addHero({ name } as Hero)
    .subscribe(hero => {
      this.heroes.push(hero);
    });
}
```

往 `HeroService` 类中添加 `addHero()` 方法。

```typescript
/** POST: add a new hero to the server */
addHero (hero: Hero): Observable<Hero> {
  return this.http.post<Hero>(this.heroesUrl, hero, httpOptions).pipe(
    tap((hero: Hero) => this.log(`added hero w/ id=${hero.id}`)),
    catchError(this.handleError<Hero>('addHero'))
  );
}
```

#### 删除某个英雄

为每个"英雄"添加一个删除按钮

```
<ul class="heroes">
  <li *ngFor="let hero of heroes">
    <a routerLink="/detail/{{hero.id}}">
      <span class="badge">{{hero.id}}</span> {{hero.name}}
    </a>
    <button class="delete" title="delete hero"
      (click)="delete(hero)">x</button>
  </li>
</ul>
```

添加delete函数到组件

```typescript
delete(hero: Hero): void {
  this.heroes = this.heroes.filter(h => h !== hero);
  this.heroService.deleteHero(hero).subscribe();
}
```

组件的 `delete()` 方法会在 `HeroService` 对服务器的操作成功之前，先从列表中移除*要删除的英雄*。

组件与 `heroService.delete()` 返回的 `Observable` 还完全没有关联。**必须订阅它**。

>如果你忘了调用 `subscribe()`，本服务将不会把这个删除请求发送给服务器。
>作为一条通用的规则，`Observable` 在有人订阅之前*什么都不会做*。

在service中添加delete方法

```typescript
/** DELETE: delete the hero from the server */
deleteHero (hero: Hero | number): Observable<Hero> {
  const id = typeof hero === 'number' ? hero : hero.id;
  const url = `${this.heroesUrl}/${id}`;

  return this.http.delete<Hero>(url, httpOptions).pipe(
    tap(_ => this.log(`deleted hero id=${id}`)),
    catchError(this.handleError<Hero>('deleteHero'))
  );
}
```

#### 根据名字搜索

在service中添加search方法

```typescript
/* GET heroes whose name contains search term */
searchHeroes(term: string): Observable<Hero[]> {
  if (!term.trim()) {
    // if not search term, return empty hero array.
    return of([]);
  }
  return this.http.get<Hero[]>(`${this.heroesUrl}/?name=${term}`).pipe(
    tap(_ => this.log(`found heroes matching "${term}"`)),
    catchError(this.handleError<Hero[]>('searchHeroes', []))
  );
}
```

创建用于搜索英雄的元素

```
ng generate component hero-search
```

html文件,当用户在搜索框中输入时，一个 *keyup* 事件绑定会调用该组件的 `search()` 方法，并传入新的搜索框的值。

```html
<div id="search-component">
  <h4>Hero Search</h4>

  <input #searchBox id="search-box" (keyup)="search(searchBox.value)" />

  <ul class="search-result">
    <li *ngFor="let hero of heroes$ | async" >
      <a routerLink="/detail/{{hero.id}}">
        {{hero.name}}
      </a>
    </li>
  </ul>
</div>

<!--
$ 是一个命名惯例，用来表明 heroes$ 是一个 Observable，而不是数组。

*ngFor 不能直接使用 Observable。 不过，它后面还有一个管道字符（|），后面紧跟着一个 async，它表示 Angular 的 AsyncPipe。

AsyncPipe 会自动订阅到 Observable，这样你就不用再在组件类中订阅了。 
-->
```

编写组件类

```
import { Component, OnInit } from '@angular/core';

import { Observable, Subject } from 'rxjs';

import {
   debounceTime, distinctUntilChanged, switchMap
 } from 'rxjs/operators';

import { Hero } from '../hero';
import { HeroService } from '../hero.service';

@Component({
  selector: 'app-hero-search',
  templateUrl: './hero-search.component.html',
  styleUrls: [ './hero-search.component.css' ]
})
export class HeroSearchComponent implements OnInit {
  heroes$: Observable<Hero[]>;
  private searchTerms = new Subject<string>();

  constructor(private heroService: HeroService) {}

  // Push a search term into the observable stream.
  search(term: string): void {
    this.searchTerms.next(term);
  }

  ngOnInit(): void {
    this.heroes$ = this.searchTerms.pipe(
      // wait 300ms after each keystroke before considering the term
      debounceTime(300),
      // 在传出最终字符串之前，debounceTime(300) 将会等待，
      //直到新增字符串的事件暂停了 300 毫秒。 你实际发起请求的间隔永远不会小于 300ms。

      // ignore new term if same as previous term
      distinctUntilChanged(),
      // distinctUntilChanged() 会确保只在过滤条件变化时才发送请求。

      // switch to new search observable each time the term changes
      switchMap((term: string) => this.heroService.searchHeroes(term)),
      // switchMap() 会为每个从 debounce 和 distinctUntilChanged 中通过的
      // 搜索词调用搜索服务。 它会取消并丢弃以前的搜索可观察对象，只保留最近的。
    );
  }
}


```

> `Subject` 既是可观察对象的数据源，本身也是 `Observable`。 你可以像订阅任何 `Observable` 一样订阅 `Subject`。
>
> 你还可以通过调用它的 `next(value)` 方法往 `Observable` 中推送一些值，就像 `search()` 方法中一样。

>   借助 [switchMap 操作符](http://www.learnrxjs.io/operators/transformation/switchmap.html)， 每个有效的击键事件都会触发一次 `HttpClient.get()` 方法调用。 即使在每个请求之间都有至少 300ms 的间隔，仍然可能会同时存在多个尚未返回的 HTTP 请求。
>
>   `switchMap()` 会记住原始的请求顺序，只会返回最近一次 HTTP 方法调用的结果。 以前的那些请求都会被取消和舍弃。
>
>   注意，*取消*前一个 `searchHeroes()` 可观察对象并不会中止尚未完成的 HTTP 请求。 那些不想要的结果只会在它们抵达应用代码之前被舍弃。