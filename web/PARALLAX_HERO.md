# 🌌 Parallax Hero Section

## Overview

The new Hero section implements a multi-layer parallax scrolling effect inspired by "Moon Light". As the user scrolls, different layers move at different speeds to create a sense of depth.

## 🎭 Parallax Layers

1. **Stars** (`stars.png`): Slow movement (speed: 0.25x)
2. **Moon** (`moon.png`): Fast movement (speed: 1.05x)
3. **Mountains Behind** (`mountains_behind.png`): Medium movement (speed: 0.5x)
4. **Hero Title**: Moves horizontally and vertically (speed: 4x right, 1.5x down)
5. **Explore Button**: Moves down (speed: 1.5x)
6. **Mountains Front** (`mountains_front.png`): Static foreground (speed: 0x)

## 🔧 Implementation

### React Refs & Scroll Logic
- Uses `useRef` to directly manipulate DOM elements for performance.
- Scroll listener updates `style.top`, `style.left`, etc. dynamically.
- `window.scrollY` drives all animations.

```javascript
// Example logic
starsRef.current.style.left = value * 0.25 + 'px';
moonRef.current.style.top = value * 1.05 + 'px';
```

### CSS Styling
- `.main-container`: Fullscreen relative container with `overflow: hidden`.
- `::before` pseudo-element: create a gradient bottom fade.
- Images use `position: absolute` to layer incorrectly.
- `mix-blend-mode: screen` on the moon for better integration.

## 🌟 Integration

The parallax section replaces the standard hero while maintaining the "Cosmic OS" branding and "Explore" functionality. It seamlessly integrates with the rest of the glassmorphic site design.
