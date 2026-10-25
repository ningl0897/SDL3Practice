# TODO — text 模块（练习 6 扩展）
记录时间：2026-10-23 00:48　｜　状态：进行中

## 一、目标
1. 修复源码各头文件依赖
2. 字体数据从 Game 迁到新类型 Text，做成可复用模块
3. 只对外公开操作函数
4. 完成练习 6 功能，新增文字屏幕弹跳动画
5. API 尚未定稿（待补）

## 二、结构体（text.h）
```c
typedef struct {
    TTF_Font    *font;         // 字体句柄
    SDL_Texture *font_texture; // 文字纹理
    SDL_FRect    frect;        // 位置与大小
    SDL_Renderer *renderer;    // 指向渲染器（不持有）
} Text;
```

## 三、对外 API（text.h）— 公开
```c
bool text_load(...);   // 加载字体与文字纹理，待定稿
void text_quit(...);   // 释放纹理与字体，待定稿
```

## 四、私有（text.c static）
```c
static void text_update(...);  // 动画在此实现
```

## 五、弹跳实现
```c
#define TEXT_SPEED 3.0f      // 速度宏
```
- 直接修改 frect 内数据
- update：当前位置 += 偏移量，碰到边界立即反向
- 边界：以屏幕宽高与 frect.w/h 判断碰撞
