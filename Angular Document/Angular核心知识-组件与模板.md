# Angular核心知识-组件与模板

## 显示数据

### 插值表达式显示属性(双花括号)

```
import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  template: `
    <h1>{{title}}</h1>
    <h2>My favorite hero is: {{myHero}}</h2>
    `
})
export class AppComponent {
  title = 'Tour of Heroes';
  myHero = 'Windstorm';
}
```

> 模板是包在 ECMAScript 2015 反引号 (```) 中的一个多行字符串。
> 反引号 (```) — 注意，不是单引号 (') — 允许把一个字符串写在多行上，
> 使 HTML 模板更容易阅读。

Angular 自动从组件中提取 `title` 和 `myHero` 属性的值，并且把这些值插入浏览器中。当这些属性发生变化时，Angular 就会自动刷新显示。

> 严格来说，“重新显示”是在某些与视图有关的异步事件之后发生的，例如，按键、定时器完成或对 HTTP 请求的响应。

### 内联 (inline) 模板vs模板文件

上一块代码`@Component` 装饰器中使用 template 属性可以将模板定义为内联的.

通过 `@Component` 装饰器中的 `templateUrl` 属性可以连接到一个独立的 HTML 文件中。

`ng generate component`生成文件时会带有文件模板, 添加参数可以不生成`ng generate component hero -it`

### 使用构造函数VS变量初始化

上一块代码使用变量赋值的方式初始化组件。还可以使用构造函数来声明和初始化属性。

```
export class AppCtorComponent {
  title: string;
  myHero: string;

  constructor() {
    this.title = 'Tour of Heroes';
    this.myHero = 'Windstorm';
  }
}
```

###  *ngFor 显示数组

先定义数组

```
export class AppComponent {
  title = 'Tour of Heroes';
  heroes = ['Windstorm', 'Bombasto', 'Magneta', 'Tornado'];
  myHero = this.heroes[0];
}
```

在模板中使用 Angular 的 ngFor 指令来显示 heroes 列表中的每一项

```
template: `
  <h1>{{title}}</h1>
  <h2>My favorite hero is: {{myHero}}</h2>
  <p>Heroes:</p>
  <ul>
    <li *ngFor="let hero of heroes">
      {{ hero }}
    </li>
  </ul>
`
```

Angular 为列表中的每个条目复制一个 `<li>` 元素，在每个迭代中，把 `hero` 变量设置为当前条目（英雄）。Angular 把 `hero` 变量作为双花括号插值表达式的上下文。

 `ngFor` 双引号表达式中的 `hero`，它是一个模板输入变量。更多模板输入变量的信息，见[模板语法](https://www.angular.cn/guide/template-syntax)中的[微语法 (microsyntax)](https://www.angular.cn/guide/template-syntax#microsyntax)。`ngFor` 可以为任何[可迭代的 (iterable) ](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Iteration_protocols)对象重复渲染条目。

### 为数据创建类

创建一个 Hero 类

```
ng generate class hero
```

代码如下：

```
export class Hero {
  constructor(
    public id: number,
    public name: string) { }
}
```

> 该范例利用的是 TypeScript 提供的简写形式 —— 用构造函数的参数直接定义属性。
>
> `public id: number,`
>
> - 声明了一个构造函数参数及其类型。
>
> - 声明了一个同名的公共属性。
>
> - 当创建该类的一个实例时，把该属性初始化为相应的参数值。

### 使用类

```
heroes = [
  new Hero(1, 'Windstorm'),
  {id: 13, name: 'Bombasto'},
  new Hero(15, 'Magneta'),
  new Hero(20, 'Tornado')
];
myHero = this.heroes[0];
```

提取属性

```
template: `
  <h1>{{title}}</h1>
  <h2>My favorite hero is: {{myHero.name}}</h2>
  <p>Heroes:</p>
  <ul>
    <li *ngFor="let hero of heroes">
      {{ hero.name }}
    </li>
  </ul>
`
```

### *ngIf 条件显示

Angular 的 `ngIf` 指令会根据一个布尔条件来显示或移除一个元素。

```
<p *ngIf="heroes.length > 3">There are many heroes!</p>
```

> Angular 并不是在显示和隐藏这条消息，它是在从 DOM 中添加和移除这个段落元素。
> 这会提高性能，特别是在一些大的项目中有条件地包含或排除一大堆带着很多数据绑定的 HTML 时。

## 模板语法

对应于模型-视图-控制器 (MVC) 或模型-视图-视图模型 (MVVM) ，在 Angular 中，组件扮演着控制器或视图模型的角色，模板则扮演视图的角色。

### 模板中的 HTML 

HTML 是 Angular 模板的语言。几乎所有的 HTML 语法都是有效的模板语法。但值得注意的例外是 `<script>` 元素，它被禁用了，以阻止脚本注入攻击的风险。（实际上，`<script>` 只是被忽略了。）The `<html>`, `<body>`, and `<base>` elements have no useful role. Pretty much everything else is fair game.

可以通过组件和指令来扩展模板中的 HTML 词汇。

### 插值表达式 ( {﻿{...}} )

插值表达式可以把计算后的字符串插入到 HTML 元素标签内的文本或对标签的属性进行赋值。

```
<h3>
  {{title}}
  <img src="{{heroImageUrl}}" style="height:30px">
</h3>
```

在括号之间的“素材”，通常是组件属性的名字。Angular 会用组件中相应属性的字符串值，替换这个名字。

一般来说，括号间的素材是一个**模板表达式**，Angular 先**对它求值**，再把它**转换成字符串**。

```
<!-- "The sum of 1 + 1 is 2" -->
<p>The sum of 1 + 1 is {{1 + 1}}</p>
```

该表达式可以调用宿主组件的方法，如下调用getVal():

```
<!-- "The sum of 1 + 1 is not 4" -->
<p>The sum of 1 + 1 is not {{1 + 1 + getVal()}}</p>
```

Angular 对所有双花括号中的表达式求值，把求值的结果转换成字符串，并把它们跟相邻的字符串字面量连接起来。最后，把这个组合出来的插值结果赋给**元素或指令的属性**。

插值表达式是一个特殊的语法，Angular 把它转换成了[属性绑定](https://www.angular.cn/guide/template-syntax#property-binding)

### 模板表达式

模板**表达式**产生一个值。 Angular 执行这个表达式，并把它赋值给绑定目标的属性，这个绑定目标可能是 HTML 元素、组件或指令。

`{{1 + 1}}` 中所包含的模板表达式是 `1 + 1`。 在[属性绑定](https://www.angular.cn/guide/template-syntax#property-binding)中会再次看到模板表达式，它出现在 `=` 右侧的引号中，就像这样：`[property]="expression"`。

编写模板表达式所用的语言看起来很像 JavaScript。 很多 JavaScript 表达式也是合法的模板表达式，但不是全部。

JavaScript 中那些具有或可能引发副作用的表达式是被禁止的，包括：

-  赋值 (`=`, `+=`, `-=`, ...)
-  `new` 运算符
-  使用 `;` 或 `,` 的链式表达式
-  自增和自减运算符：`++` 和 `--`

和 JavaScript 语 法的其它显著不同包括：

-  不支持位运算 `|` 和 `&`
-  具有新的[模板表达式运算符](https://www.angular.cn/guide/template-syntax#expression-operators)，比如 `|`、`?.` 和 `!`。

#### 表达式上下文

典型的*表达式上下文*就是这个**组件实例**，它是各种绑定值的来源。 在下面的代码片段中，双花括号中的 `title` 和引号中的 `isUnchanged` 所引用的都是 `AppComponent` 中的属性。`      `

```
{{title}}
<span [hidden]="isUnchanged">changed</span>
```

表达式的上下文可以包括组件之外的对象。比如[模板输入变量](https://www.angular.cn/guide/template-syntax#template-input-variable) (`let hero`)和[模板引用变量](https://www.angular.cn/guide/template-syntax#ref-vars)(`#heroInput`)就是备选的上下文对象之一。

```
<div *ngFor="let hero of heroes">{{hero.name}}</div>
<input #heroInput> {{heroInput.value}}
```

### 模板语句

模板**语句**用来响应由绑定目标（如 HTML 元素、组件或指令）触发的**事件**。模板语句将在[事件绑定](https://www.angular.cn/guide/template-syntax#event-binding)一节看到，它出现在 `=` 号右侧的引号中，就像这样：`(event)="statement"`。

```
<button (click)="deleteHero()">Delete hero</button>
```

和模板表达式一样，模板*语句*使用的语言也像 JavaScript。 模板语句解析器和模板表达式解析器有所不同，特别之处在于它支持基本赋值 (`=`) 和表达式链 (`;` 和 `,`)。

然而，某些 JavaScript 语法仍然是不允许的：

-  `new` 运算符
-  自增和自减运算符：`++` 和 `--`
-  操作并赋值，例如 `+=` 和 `-=`
-  位操作符 `|` 和 `&`
-  [模板表达式运算符](https://www.angular.cn/guide/template-syntax#expression-operators)

#### 语句上下文

和表达式中一样，语句只能引用语句上下文中 —— 通常是正在绑定事件的那个**组件实例**。

典型的*语句上下文*就是当前组件的实例。 `(click)="deleteHero()"` 中的 *deleteHero* 就是这个数据绑定组件上的一个方法。

```
<button (click)="deleteHero()">Delete hero</button>
```

语句上下文可以引用模板自身上下文中的属性。在下面的例子中，就把模板的 `$event` 对象、[模板输入变量](https://www.angular.cn/guide/template-syntax#template-input-variable) (`let hero`)和[模板引用变量](https://www.angular.cn/guide/template-syntax#ref-vars) (`#heroForm`)传给了组件中的一个事件处理器方法。

```
<button (click)="onSave($event)">Save</button>
<button *ngFor="let hero of heroes" (click)="deleteHero(hero)">{{hero.name}}</button>
<form #heroForm (ngSubmit)="onSubmit(heroForm)"> ... </form>
```

模板上下文中的变量名的优先级高于组件上下文中的变量名。在上面的 `deleteHero(hero)` 中，`hero` 是一个模板输入变量，而不是组件中的 `hero` 属性。

模板语句不能引用全局命名空间的任何东西。比如不能引用 `window` 或 `document`，也不能调用 `console.log` 或 `Math.max`。

### 绑定语法：概览

绑定的类型可以根据数据流的方向分成三类：**从数据源到视图**、**从视图到数据源**以及双向的**从视图到数据源再到视图**。

| 数据方向                 | 语法                                                         | 绑定类型                                                 |
| ------------------------ | ------------------------------------------------------------ | -------------------------------------------------------- |
| 单向<br />从数据源到视图 | `{{expression}}`<br />`[target]="expression"`<br />`bind-target="expression"` | 插值表达式<br />属性<br />Attribute<br />CSS类<br />样式 |
| 单向<br />从视图到数据源 | `(target)="statement"`<br />`on-target="statement"`          | 事件                                                     |
| 双向                     | `[(target)]="expression"`<br />`bindon-target="expression"`  | 双向                                                     |

#### 新的思维模型

> ### HTML attribute 与 DOM property 的对比
>
> 要想理解 Angular 绑定如何工作，重点是搞清 HTML attribute 和 DOM property 之间的区别。
>
> **attribute 是由 HTML 定义的。property 是由 DOM (Document Object Model) 定义的。**
>
> -  少量 HTML attribute 和 property 之间有着 1:1 的映射，如 `id`。
> -  有些 HTML attribute 没有对应的 property，如 `colspan`。
> -  有些 DOM property 没有对应的 attribute，如 `textContent`。
> -  大量 HTML attribute 看起来映射到了 property…… 但却不像你想的那样！
>
> 最后一类尤其让人困惑…… 除非你能理解这个普遍原则：
>
> **attribute 初始化 DOM property，然后它们的任务就完成了。property 的值可以改变；attribute 的值不能改变。**
>
> 例如，当浏览器渲染 `<input type="text" value="Bob">` 时，它将创建相应 DOM 节点， 它的 `value` 这个 property 被*初始化为* “Bob”。
>
> 当用户在输入框中输入 “Sally” 时，DOM 元素的 `value` 这个 *property* 变成了 “Sally”。 但是该 HTML 的 `value` 这个 *attribute* 保持不变。如果你读取 input 元素的 attribute，就会发现确实没变： `input.getAttribute('value') // 返回 "Bob"`。
>
> HTML 的 `value` 这个 attribute 指定了*初始*值；DOM 的 `value` 这个 property 是*当前*值。
>
> `disabled` 这个 attribute 是另一种特例。按钮的 `disabled` 这个 *property* 是 `false`，因为默认情况下按钮是可用的。 当你添加 `disabled` 这个 *attribute* 时，只要它出现了按钮的 `disabled` 这个 *property* 就初始化为 `true`，于是按钮就被禁用了。
>
> 添加或删除 `disabled` 这个 *attribute* 会禁用或启用这个按钮。但 *attribute* 的值无关紧要，这就是你为什么没法通过 `<button disabled="false">仍被禁用</button>` 这种写法来启用按钮。
>
> 设置按钮的 `disabled` 这个 *property*（如，通过 Angular 绑定）可以禁用或启用这个按钮。 这就是 *property* 的价值。
>
> **就算名字相同，HTML attribute 和 DOM property 也不是同一样东西。**

在 Angular 的世界中，attribute 唯一的作用是用来初始化元素和指令的状态。
当进行数据绑定时，只是在与元素和指令的 property 和事件打交道，而 attribute 就完全靠边站了。

#### 绑定目标

| 绑定类型  | 目标                                                   | 范例                                                         |
| --------- | ------------------------------------------------------ | ------------------------------------------------------------ |
| 属性      | 元素的property<br />组件的property<br />指令的property | `<img [src]="heroImageUrl">
<br/><app-hero-detail [hero]="currentHero"></app-hero-detail>
<div [ngClass]="{'special': isSpecial}"></div>` |
| 事件      | 元素的事件<br />组件的事件<br />指令的事件             | `<button (click)="onSave()">Save</button>
<br/><app-hero-detail (deleteRequest)="deleteHero()"></app-hero-detail>
<div (myClick)="clicked=$event" clickable>click me</div>` |
| 双向      | 事件与property                                         | `<input [(ngModel)]="name">`                                 |
| Attribute | attribute（例外情况）                                  | `<button [attr.aria-label]="help">help</button>`             |
| CSS 类    | class property                                         | `<div [class.special]="isSpecial">Special</div>`             |
| 样式      | style property                                         | `<button [style.color]="isSpecial ? 'red' : 'green'">`       |

### 属性绑定（【属性名】）

当要把视图元素的属性 (property) 设置为[模板表达式](https://www.angular.cn/guide/template-syntax#template-expressions)时，就要写模板的**属性 (property) 绑定**。

一个例子是设置自定义组件的模型属性（这是父子组件之间通讯的重要途径）：

```
<app-hero-detail [hero]="currentHero"></app-hero-detail>
```

#### 单向输入

人们经常把属性绑定描述成*单向数据绑定*，因为值的流动是单向的，从组件的数据属性流动到目标元素的属性。

- 不能使用属性绑定来从目标元素拉取值，也不能绑定到目标元素的属性来读取它。只能设置它。

- 也不能使用属性 绑定 来**调用**目标元素上的方法。

- 如果这个元素触发了事件，可以通过[事件绑定](https://www.angular.cn/guide/template-syntax#event-binding)来监听它们。

- 如果必须读取目标元素上的属性或调用它的某个方法，得用另一种技术。
  参见 API 参考手册中的[ViewChild](https://www.angular.cn/api/core/ViewChild) 和[ContentChild](https://www.angular.cn/api/core/ContentChild)。

#### 绑定目标

包裹在方括号中的元素属性名标记着目标属性。

```
<img [src]="heroImageUrl">
```

`bind-` 前缀的可选形式，称之为**规范形式**：

```
<img bind-src="heroImageUrl">
```

目标的名字总是 property 的名字。即使它看起来和别的名字一样。看到 `src` 时，可能会把它当做 attribute。不！它不是！它是 image 元素的 property 名。

元素属性可能是最常见的绑定目标，但 Angular 会先去看这个名字是否是某个已知指令的属性名，如下例子：

```
<div [ngClass]="classes">[ngClass] binding to the classes property</div>
```

> 严格来说，Angular 正在匹配指令的[输入属性](https://www.angular.cn/guide/template-syntax#inputs-outputs)的名字。这个名字是指令的 `inputs` 数组中所列的名字，或者是带有 `@Input()` 装饰器的属性。这些输入属性被映射为指令自己的属性。

如果名字没有匹配上已知指令或元素的属性，Angular 就会报告“未知指令”的错误。

#### 消除副作用

表达式中可以调用像 `getFoo()` 这样的方法。只有你知道 `getFoo()` 干了什么。如果 `getFoo()` 改变了某个东西，恰好又绑定到个这个东西，你就可能把自己坑了。
Angular 可能显示也可能不显示变化后的值。Angular 还可能检测到变化，并抛出警告型错误。

一般建议是，只绑定数据属性和那些只返回值而不做其它事情的方法。

#### 返回恰当的类型

模板表达式应该返回目标属性所需类型的值。如果目标属性想要个字符串，就返回字符串。如果目标属性想要个数字，就返回数字。如果目标属性想要个对象，就返回对象。

如下`HeroDetail` 组件的 `hero` 属性想要一个 `Hero` 对象，那就在属性绑定中精确地给它一个 `Hero` 对象：

```
<app-hero-detail [hero]="currentHero"></app-hero-detail>
```

#### 别忘了方括号

方括号告诉 Angular 要计算模板表达式。如果忘了加方括号，Angular 会把这个表达式当做字符串常量看待，并用该字符串来*初始化目标属性*。它*不会*计算这个字符串。

下面是个错误示例

```
<!-- ERROR: HeroDetailComponent.hero expects a
     Hero object, not the string "currentHero" -->
  <app-hero-detail hero="currentHero"></app-hero-detail>
```

#### 一次性字符串初始化

当满足下列条件时，*应该*省略括号：

-  目标属性接受字符串值。
-  字符串是个固定值，可以直接合并到模块中。
-  这个初始值永不改变。

你经常这样在标准 HTML 中用这种方式初始化 attribute，这种方式也可以用在初始化指令和组件的属性。
下面这个例子把 `HeroDetailComponent` 的 `prefix` 属性初始化为固定的字符串，而不是模板表达式。Angular 设置它，然后忘记它。

```
<app-hero-detail prefix="You are my" [hero]="currentHero"></app-hero-detail>
```

作为对比，`[hero]` 绑定是组件的 `currentHero` 属性的活绑定，它会一直随着更新。

#### 属性绑定 VS 插值表达式

通常得在插值表达式和属性绑定之间做出选择。下列这几对绑定做的事情完全相同：

```
<p><img src="{{heroImageUrl}}"> is the <i>interpolated</i> image.</p>
<p><img [src]="heroImageUrl"> is the <i>property bound</i> image.</p>

<p><span>"{{title}}" is the <i>interpolated</i> title.</span></p>
<p>"<span [innerHTML]="title"></span>" is the <i>property bound</i> title.</p>
```

在多数情况下，插值表达式是更方便的备选项。
实际上，在渲染视图之前，Angular 把这些插值表达式翻译成相应的属性绑定。

当要渲染的数据类型是字符串时，没有技术上的理由证明哪种形式更好。

但数据类型不是字符串时，就必须使用**属性绑定**。

##### 内容安全

假设下面恶意内容：（？？？）

```
evilTitle = 'Template <script>alert("evil never sleeps")</script>Syntax';
```

Angular 数据绑定对危险 HTML 有防备。在显示它们之前，它对内容先进行*消毒*。不管是插值表达式还是属性绑定，都**不会**允许带有 script 标签的 HTML 泄漏到浏览器中。

```
<!--
  Angular generates warnings for these two lines as it sanitizes them
  WARNING: sanitizing HTML stripped some content (see http://g.co/ng/security#xss).
 -->
<p><span>"{{evilTitle}}" is the <i>interpolated</i> evil title.</span></p>
<p>"<span [innerHTML]="evilTitle"></span>" is the <i>property bound</i> evil title.</p>
```

插值表达式处理 script 标签与属性绑定有所不同，但是二者都只渲染没有危害的内容。

![evil title made safe](https://www.angular.cn/generated/images/guide/template-syntax/evil-title.png)

#### attribute、class 和 style 绑定

##### attribute 绑定

可以通过**attribute 绑定**来直接设置 attribute 的值。

> 这是“绑定到目标属性 (property)”这条规则中唯一的例外。这是唯一的能创建和设置 attribute 的绑定形式。

本章中，通篇都在说通过属性绑定来设置元素的属性总是好于用字符串设置 attribute。为什么 Angular 还提供了 attribute 绑定呢？

如果想写出类似下面这样的东西，就会暴露出痛点了：

```
      
<tr><td colspan="{{1 + 1}}">Three-Four</td></tr>     
```

会得到这个错误：

```
      
Template parse errors: Can't bind to 'colspan' since it isn't a known native property     
```

正如提示中所说，`<td>` 元素没有 `colspan` 属性。 但是插值表达式和属性绑定只能设置*属性*，不能设置 attribute。

你需要 attribute 绑定来创建和绑定到这样的 attribute。

attribute 绑定的语法与属性绑定类似。但方括号中的部分不是元素的属性名，而是由**attr**前缀，一个点 (`.`) 和 attribute 的名字组成。可以通过值为字符串的表达式来设置 attribute 的值。

这里把 `[attr.colspan]` 绑定到一个计算值：

```
<table border=1>
  <!--  expression calculates colspan=2 -->
  <tr><td [attr.colspan]="1 + 1">One-Two</td></tr>

  <!-- ERROR: There is no `colspan` property to set!
    <tr><td colspan="{{1 + 1}}">Three-Four</td></tr>
  -->

  <tr><td>Five</td><td>Six</td></tr>
</table>
```

attribute 绑定的主要用例之一是设置 ARIA attribute（译注：ARIA 指可访问性，用于给残障人士访问互联网提供便利），就像这个例子中一样：

```
<!-- create and set an aria attribute for assistive technology -->
<button [attr.aria-label]="actionName">{{actionName}} with Aria</button>
```

##### CSS类绑定

借助 CSS 类绑定，可以从元素的 `class` attribute 上添加和移除 CSS 类名。

CSS 类绑定绑定的语法与属性绑定类似。但方括号中的部分不是元素的属性名，而是由**class**前缀，一个点 (`.`)和 CSS 类的名字组成，其中后两部分是可选的。形如：`[class.class-name]`。

下列例子示范了如何通过 CSS 类绑定来添加和移除应用的 "special" 类。不用绑定直接设置 attribute 时是这样的：

```
<!-- standard class attribute setting  -->
<div class="bad curly special">Bad curly special</div>
```

可以把它改写为绑定到所需 CSS 类名的绑定；这是一个或者全有或者全无的替换型绑定。
（译注：即当 badCurly 有值时 class 这个 attribute 设置的内容会被完全覆盖）

```
<!-- reset/override all class names with a binding  -->
<div class="bad curly special"
     [class]="badCurly">Bad curly</div>
```

最后，可以绑定到特定的类名。当模板表达式的求值结果是真值时，Angular 会添加这个类，反之则移除它。

```
<!-- toggle the "special" class on/off with a property -->
<div [class.special]="isSpecial">The class binding is special</div>

<!-- binding to `class.special` trumps the class attribute -->
<div class="special"
     [class.special]="!isSpecial">This one is not so special</div>
```

> 人们通常更喜欢使用 [NgClass 指令](https://www.angular.cn/guide/template-syntax#ngClass) 来同时管理多个类名。

##### 样式绑定

通过**样式绑定**，可以设置内联样式。

样式绑定的语法与属性绑定类似。 但方括号中的部分不是元素的属性名，而由**style**前缀，一个点 (`.`)和 CSS 样式的属性名组成。 形如：`[style.style-property]`。

```
<button [style.color]="isSpecial ? 'red': 'green'">Red</button>
<button [style.background-color]="canSave ? 'cyan': 'grey'" >Save</button>
```

有些样式绑定中的样式带有单位。在这里，以根据条件用 “em” 和 “%” 来设置字体大小的单位。

```
<button [style.font-size.em]="isSpecial ? 3 : 1" >Big</button>
<button [style.font-size.%]="!isSpecial ? 150 : 50" >Small</button>
```

> 虽然这是设置单一样式的好办法，但人们通常更喜欢使用 [NgStyle 指令](https://www.angular.cn/guide/template-syntax#ngStyle) 来同时设置多个内联样式。
>
> 注意，*样式属性*命名方法可以用[中线命名法](https://www.angular.cn/guide/glossary#dash-case)，像上面的一样也可以用[驼峰式命名法](https://www.angular.cn/guide/glossary#camelcase)，如`fontSize`。

### 事件绑定（ (event) ）

知道用户动作的唯一方式是监听某些事件，如按键、鼠标移动、点击和触摸屏幕。可以通过 Angular 事件绑定来声明对哪些用户动作感兴趣。

事件绑定语法由等号左侧带圆括号的**目标事件**和右侧引号中的[模板语句](https://www.angular.cn/guide/template-syntax#template-statements)组成。下面事件绑定监听按钮的点击事件。每当点击发生时，都会调用组件的 `onSave()` 方法。

```
<button (click)="onSave()">Save</button>
```

##### 目标事件

**圆括号中的名称** —— 比如 `(click)` —— 标记出目标事件。在下面例子中，目标是按钮的 click 事件。

```
<button (click)="onSave()">Save</button>
```

带 `on-` 前缀的备选形式，称之为规范形式：

```
<button on-click="onSave()">On Save</button>
```

元素事件可能是更常见的目标，但 Angular 会先看这个名字是否能匹配上已知指令的事件属性，就像下面这个例子：

```
<!-- `myClick` is an event on the custom `ClickDirective` -->
<div (myClick)="clickMessage=$event" clickable>click with myClick</div>
```

> 更多关于该 `myClick` 指令的解释，见[给输入/输出属性起别名](https://www.angular.cn/guide/template-syntax#aliasing-io)。

如果这个名字没能匹配到元素事件或已知指令的输出属性，Angular 就会报“未知指令”错误。

##### $event 和事件处理语句

绑定会通过**名叫 $event 的事件对象**传递关于此事件的信息（包括数据值）。

事件对象的形态取决于目标事件。如果目标事件是原生 DOM 元素事件，
`$event` 就是 [DOM 事件对象](https://developer.mozilla.org/en-US/docs/Web/Events)，它有像 `target` 和 `target.value` 这样的属性。

考虑这个范例：

```
<input [value]="currentHero.name"
       (input)="currentHero.name=$event.target.value" >
```

当用户造成更改时，`input` 事件被触发，并在包含了 DOM 事件对象 (`$event`) 的上下文中执行这条语句。

要更新 `name` 属性，就要通过路径 `$event.target.value` 来获取更改后的值。

如果事件属于指令（回想一下，组件是指令的一种），那么 `$event` 具体是什么由指令决定。（参考下例）

##### 使用 EventEmitter 实现自定义事件

通常，指令使用 Angular [EventEmitter](https://www.angular.cn/api/core/EventEmitter) 来触发自定义事件。指令创建一个 `EventEmitter` 实例，并且把它作为属性暴露出来。指令调用 `EventEmitter.emit(payload)` 来触发事件，可以传入任何东西作为消息载荷。父指令通过绑定到这个属性来监听事件，并通过 `$event` 对象来访问载荷。

假设 `HeroDetailComponent` 用于显示英雄的信息，并响应用户的动作。 虽然 `HeroDetailComponent` 包含删除按钮，但它自己并不知道该如何删除这个英雄。 最好的做法是触发事件来报告“删除用户”的请求。

下面的代码节选自 `HeroDetailComponent`：

```
template: `
<div>
  <img src="{{heroImageUrl}}">
  <span [style.text-decoration]="lineThrough">
    {{prefix}} {{hero?.name}}
  </span>
  <button (click)="delete()">Delete</button>
</div>`
```

```
// This component makes a request but it can't actually delete a hero.
deleteRequest = new EventEmitter<Hero>();

delete() {
  this.deleteRequest.emit(this.hero);
}
```

组件定义了 `deleteRequest` 属性，它是 `EventEmitter` 实例。 当用户点击*删除*时，组件会调用 `delete()` 方法，让 `EventEmitter` 发出一个 `Hero` 对象。

现在，假设有个宿主的父组件，它绑定了 `HeroDetailComponent` 的 `deleteRequest` 事件。

```
<app-hero-detail (deleteRequest)="deleteHero($event)" [hero]="currentHero"></app-hero-detail>
```

当 `deleteRequest` 事件触发时，Angular 调用父组件的 `deleteHero` 方法，在 `$event` 变量中传入*要删除的英雄*（来自 `HeroDetail`）。

##### 模板语句有副作用

模板语句的副作用不仅没问题，反而正是所期望的。它可能更新模型，还可能触发其它修改，包括向远端服务器的查询和保存。这些变更通过系统进行扩散，并最终显示到当前以及其它视图中。

#### 双向数据绑定 TODO

在元素层面上，既要设置元素属性，又要监听元素事件变化。Angular 为此提供一种特殊的*双向数据绑定*语法：**[(x)]**。 `[(x)]` 语法结合了*属性绑定*的方括号 `[x]` 和*事件绑定*的圆括号 `(x)`。

### 内置指令

