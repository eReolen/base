# Media: VideoTool

@see https://git.drupalcode.org/sandbox/jcbl-1977598

Media: VideoTool integrates with the Media module to make VideoTool videos
available as file entities. Users can insert VideoTool videos with file fields
 or directly into into WYSIWYG text areas with the Media module insert button.


## File fields

- Add a new "file" type field to your content type or entity. Choose the widget
  type "Multimedia browser". You can also select an existing file field.
- While setting up the field (or after selecting "edit" on an existing field)
  enable:
    - Enabled browser plugins: "Web"
    - Allowed remote media types: "Video"
    - Allowed URI schemes: "videotool:// (VideoTool videos)"

- On "Manage display" for the file field's content or entity type, choose
  "Rendered file" and a view mode.
- Set up VideoTool video formatter options for each view mode in Structure ->
  File types -> Manage file display. This is where you can choose size, autoplay,
  appearance, and special JS API integration options.
- When using the file field while creating or editing content, paste a VideoTool
  video url into the Web tab.

ProTip: You can use multiple providers (e.g., Media: YouTube, Media: Vimeo and Media: VideoTool)
on the same file field.


## WYSIWYG inserts

- Enable the Media module "Media insert" button on your WYSIWYG profile.
- Enable "Convert Media tags to markup" filter in the appropriate text formats.
- Configure any desired settings in Configuration -> Media -> "Media browser
  settings"
- Set up VideoTool video formatter options in Structure -> File types -> Manage
  file display. **Note:** for any view mode that will be used in a WYSIWYG,
  enable both the VideoTool video and preview image formatter. Arrange the Video
  formatter on top. This allows the video to be used when the content is viewed,
  and the preview when the content is being edited.

- When editing a text area with your WYSIWYG, click the "Media insert" button,
  and paste a VideoTool video url into the Web tab of the media browser.
