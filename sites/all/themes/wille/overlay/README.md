# Orla overlay implementation in ereolenGO theme

1. Copy folder overlay(Supplied from eReolen) to Wille theme (`sites/all/themes/wille`)

2. Paste this line:

 `<script src="<?php print drupal_get_path('theme', 'wille') . '/overlay/overlay.js'; ?>"></script>`

in to the file `sites/all/themes/wille/templates/system/html.tpl.php` right before the `</body>`

3. Clear cache and reload the page.

## Note about video paths

I have changed the paths to the videos in  `overlay.js` in order for them to load.

```js
const chosenVideo = [
      {
        videoPathMov: "sites/all/themes/wille/overlay/videos/orla/orla.mov",
        videoPathWebm: "sites/all/themes/wille/overlay/videos/orla/orla.webm",
        animate: false,
      },
      {
        videoPathMov: "sites/all/themes/wille/overlay/videos/pig/pig.mov",
        videoPathWebm: "sites/all/themes/wille/overlay/videos/pig/pig.webm",
        animate: true,
      },
    ];
```

