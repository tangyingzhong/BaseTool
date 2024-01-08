# BaseTool
这是一个工具集合，从POCO1.12.5等其他第三方库封装得来
旨在为大家提供一个更为简单易于理解的API接口，省去研究第三方库的繁杂时间

# 环境准备
1、如果第三方库有变动，需要重新编译，并将库拷贝至ShareLib目录下
2、这是一个跨平台的工程，MAC上需要有clang编译器支持，windows上需要有vs2019的cl.exe支持

# 如何使用
编译结束后，直接拷贝build/Debug或者Release目录出去使用即可，头文件直接使用Tool目录下的
不需要单独拷贝其他第三方库，工程编译帮你做好