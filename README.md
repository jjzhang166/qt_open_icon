**qt_open_icon**

有木有在做QT项目时候为了一个按钮不同状态贴图而烦恼，命名只需要变化图标几种颜色，却必须贴若干个图，即难维护又浪费存储资源。这个小项目就能帮到你。我们脱离笨重的贴图，仅仅使用非常小的字体库。这样做有如下优点：

 - 多个图标字体合成一个字体文件，避免每张图片都需要联网请求；
 - 字体可任意缩放，而图片放大会失真、缩小则浪费像素；
 - 可通过css任意改变颜色、大小等

**运行说明**

基于qt5.2.1编译，需要把项目resourse下的ttf字体库文件放到运行目录下，也可以自己在程序中指定字体库目录。如果想自定义图标，可以借助阿里巴巴矢量图库平台：http://iconfont.cn/

**欢迎加入更多字体库**

![](http://git.oschina.net/coffeeLVeris/images/blob/master/mui.png)
![](http://git.oschina.net/coffeeLVeris/images/raw/master/icon1.png)