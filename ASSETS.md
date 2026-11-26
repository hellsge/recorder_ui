# assets 素材与字体索引

`assets/elements/` 存放平铺的全部 UI 切图（**98 张 PNG**），`assets/` 存放两个 Inter 字体面。
设计基准 **450x390**（屏是 390x450 竖屏，UI 横屏渲染）。

本文件放在 `assets/` 之外是刻意的：`assets/` 下的文件都会被转换打包进 romfs，文档放进去会白占 flash。

- 图片引用：`src="assets/elements/<文件名>.png"`，全 ASCII、无子目录
- 字体引用：`fontFile="/Inter-SemiBold.ttf"`（开头 `/`，路径相对 `assets/`）
- 命名：`<页面前缀>_<类型>_<名称>.png`，全局唯一
- 效果图在工作区根目录 `ui_assets/screens/<同类目录>/`（只作设计基准，不参与打包）
- `assets/` 下的每张 png 都会被打包，**即使 HML 没有引用**；所以不用的切图必须删掉才省 flash

## 文本一律用字体渲染

原稿用的是 **SF Pro**（Apple 系统字体）。字高、字宽、字形重合度三项实测都指向它；
`Inter` 是最接近且可自由分发的替代（SIL OFL 1.1），在 26/27/52px 下与原图肉眼无差。

| 文件 | 字重 | 字符集 | 大小 |
| --- | --- | --- | --- |
| `assets/Inter-SemiBold.ttf` | 600 | ASCII + `·•…–—‘’“”°`（105 字符） | ~42 KB |
| `assets/Inter-Bold.ttf` | 700 | 同上 | ~42 KB |

```xml
<hg_label text="Saved" fontFile="/Inter-SemiBold.ttf" fontType="vector"
          fontSize="27" renderMode="4" color="#ffffff" />
```

字号与颜色（按效果图实测，字高误差 0px）：

| 用途 | fontSize | 颜色 |
| --- | --- | --- |
| 状态栏日期 / 时间 | 26 | `#ffffff` |
| 正文、胶囊文案、文案条 | 26–29（多数 27） | `#ffffff` |
| 副文案（`Retry in app`、`keep USB connected`） | 26 | `#6a6a6a` |
| 强调（`Mark saved · no screenshot`） | 27 | `#f3bb63` |
| 告警（`Storage low`、`Low battery`） | 26–27 | `#ff3141` |
| 大计时 `00:24:18` | 52 | `#ffffff` |

- `fontType="vector"` 一个字体面覆盖任意字号；`renderMode="4"`（4 位抗锯齿）与效果图一致，用 `1` 会出锯齿。
- 动态文本（日期、倒计时数字、百分比）走 `characterSets`；静态文案写 `text`（或多语言用 `i18nKey`）。
- **ttf 不进 romfs**：构建期按「字体文件 + fontSize + fontType + renderMode」分组转成 `<名>_vector.bin`，只转 HML 实际用到的字符，所以加字号/换字重不会明显涨固件。
- `assets/NotoSansSC-Medium.ttf`（11 MB）是扩展注入的默认中文字体，当前没有中文文案也没有 `fontFile` 指向它，只作构建输入，删掉不影响编译。
- 许可证 `recorder_ui/Inter-LICENSE.txt`（OFL 1.1）：随固件分发时需一并提供，故同样放在 `assets/` 外。

## 素材清单

| 前缀 | 页面 | 数量 | 效果图目录 |
| --- | --- | --- | --- |
| `bg_` | 全屏背景 | 1 | — |
| `inactive_` | 01 未激活 | 28 | `screens/01-未激活` |
| `lidopen_` | 02 开盖-未激活 | 5 | `screens/02-开盖-未激活` |
| `lidclosed_` | 03 合盖-不同状态 | 3 | `screens/03-合盖-不同状态` |
| `record_` | 04 录音界面 | 3 | `screens/04-录音界面` |
| `meeting_` | 05 切换会议 | 3 | `screens/05-切换会议` |
| `idea_` | 06 灵感妙计 | 21 | `screens/06-灵感妙计` |
| `upgrade_` | 07 固件升级 | 14 | `screens/07-固件升级` |
| `upgc_` | 08 固件升级（合盖） | 13 | `screens/08-固件升级（合盖）` |
| `error_` | 09 异常状态 | 3 | `screens/09-异常状态` |
| `common_` | 公共（状态栏/灵动岛） | 4 | 跨页面 |

## 类型码

| 类型 | 含义 | 例 |
| --- | --- | --- |
| `ic` | 单个图标 | `inactive_ic_check.png` 48x48 |
| `ring` | 加载/进度环逐帧 | `inactive_ic_ring_01–15`、`upgc_ring_01–11` |
| `bar` | 升级进度条 | `upgrade_bar_track`（成品帧，非底轨） |
| `pill` | 灵动岛胶囊逐帧 01–20 | `idea_pill_01.png` 364x70 |
| `dial` | 模式盘选中态 | `meeting_ic_dial_b.png` 282x390 |

## 跨页面借用

状态栏是各页面共用的，相关素材只有一份，**不复制到各页面目录**；文字部分一律用字体渲染。

| 页面 | 借用的文件 | 位置 |
| --- | --- | --- |
| 全部页面 | 状态栏小图标：`inactive_ic_laptop_on` / `_off`、`inactive_ic_battery_*`（6 种）、`inactive_ic_headset_green` / `_red` | 01 未激活 |
| 03 合盖 | `common_ic_cloud` | common_ |
| 04 录音 | `common_ic_cloud`、`common_ic_arrow`、`common_ic_wave_color`、`common_ic_rec_dot` | common_ |
| 05 会议 | `common_ic_rec_dot`（`REC` 文字另用字体画） | common_ |
| 09 异常 | `common_ic_arrow`、`common_ic_wave_color` | common_ |

## 易混对照（同名不同尺寸，别拿错）

| 用途 | 文件 | 尺寸 |
| --- | --- | --- |
| 页面中央大图标 | `lidopen_ic_laptop_ok` / `_fail` / `_chat` | 162x162 |
| 状态栏小图标 | `inactive_ic_laptop_on` / `_off` | 28x24 |
| 页面中央大耳机 | `lidopen_ic_headset_ok` / `_fail` | 213x157 |
| 状态栏耳机 | `inactive_ic_headset_green` / `_red` | 36x34 |
| 录音页耳机 | `record_ic_headset` | 41x32 |
| 录音波形（彩色） | `common_ic_wave_color` | 381x80 |
| 会议波形 | `meeting_ic_wave_mid` | 261x87 |
| 细波形（录音/异常） | `record_ic_wave_flat` / `error_ic_wave_flat` | 351x67 |
| 进度条（升级页） | `upgrade_bar_track` | 372x26 |
| 进度环（合盖） | `upgc_ring_*` | 165x170 |

## 已知事项

- `record_ic_wave_flat` 与 `error_ic_wave_flat` 相差 0.84% 像素（波形笔触不同），是两个不同帧，**不要互换**。
- `idea_ic_bubble.png` 与 `inactive_ic_voice_bubble.png` 只差 5 个像素（取整噪声），**待定是否合并**；合并后 06 改用 `inactive_ic_voice_bubble.png`。
- 三张「图标 + 文字」复合图已把文字裁掉，只留图标并按 `<前缀>_ic_<名称>` 改名：`upgrade_ic_badge_fail.png`（45x45，紫环红叉）、`upgrade_ic_badge_ok.png`（45x46，紫环绿勾）、`common_ic_rec_dot.png`（18x19，红点）。对应的文案改用字体渲染。
- `common_ic_rec_dot.png` 是原图直接裁出来的红点，左边缘在原稿里就被裁掉了一点，画圆不完整；要更规整可以用控件画个圆。
- 工作区根目录的 `ui_assets/wave_anim/` 是竖屏 390x450 出的录音波形逐帧包，与横屏画布方向不一致，尚未导入。
- `meeting_ic_dial_b/_c.png`（282x390）在效果图里是**按 1:1 绘制、左侧被屏边裁掉 132 px**，HML 用 `x="-132"`。
  不要写成缩放 transform：缩放后盘面上的 A/B/C 和 `Mode` 文字位置与效果图对不上（字在图内）。
- `idea_ic_bubble.png` 源文件 55x55，效果图里是 62x62，HML 直接声明 62x62 由 ImageGenerator 自动放大。
- `·`（U+00B7）之类非 ASCII 字形**必须写真实字符**并在该标签上给 `characterSets`
  （`[{&quot;type&quot;:&quot;string&quot;,&quot;value&quot;:&quot;·&quot;}]`）：写成 `&#183;` 会被当字面量画出来，
  而且字体子集默认只打包 HML 里出现过的字符，不加 `characterSets` 会缺字。
- 逐帧动画的帧素材（`inactive_ic_ring_*`、`idea_pill_*`、`upgc_ring_01–11`）在 HML 里是
  **一个 `hg_image` 运行时换 `src`**（A0 用 `imageSequence`，F0/E0 每帧一段 `changeImage`）。
  `changeImage` 只在段入口触发一次，所以一帧必须占一段。这些帧必须全部留在 `conversion.json` 里。
  sim 没有 XIP，大图换 `src` 会因反复 malloc 一整帧而停在第一帧，帧动画的观感只能上板确认。

## 处理记录

| 阶段 | 结果 |
| --- | --- |
| 原始素材 | 288 张，两级中文目录，文件名含 Frame 编号 |
| 英文重命名 + 平铺 | 338 个文件改名（screens + elements），全 ASCII |
| 像素去重 | 288 → 179：日期/数字统一到 common 67 张、单页面共用图标删 common 副本 19 张、多页面共用删除页面副本 8 张、05 大时间图集 12 张、08 文案副本 2 张、01 `ring_start` 1 张 |
| 纯文字图删除 | 179 → 98：`*_tx_*` 29 张、`common_glyph_*` 37 张、`record_time_*` 12 张、`upgrade_pct_*` 2 张、`idea_time_colon` 1 张，全部改由 Inter 渲染 |
| 复合图裁字 | `upgrade_tx_failed_icon` / `upgrade_tx_updated_icon` / `common_ic_rec` 三张裁掉文字，留下图标并改名为 `upgrade_ic_badge_fail` / `upgrade_ic_badge_ok` / `common_ic_rec_dot`，总数仍为 98 |
| 文档图片移出 | `ui_workflow.png` 已删除（转换后 66 MB，会撑爆 USER_DATA1），原图在工作区根目录 |

原始版本（含旧目录结构与全部重复件）备份在工作区根目录 `ui_assets/elements/`，未改动。
