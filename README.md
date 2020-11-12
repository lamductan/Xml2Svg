SVG Parser and Renderer
==========

## Parser

![screenshot of some splines rendered with the sample program](/docs/screenshot.png?raw=true)

This is a simple project that receives input as a SVG image then produces output as drawing this image to console output by using C++ graphics libraries, particularly GDI+ or CImg. 

This project supports a some basic attributes of svg objects, such as stroke, stroke-width, stroke-opacity, fill, transform; and some basic shapes, such as polygon, polyline, circle, ellipse, rectangle, text and group objects.

## Technology Usage
- C++
- Object Oriented Programming:
  - Inheritance
  - Encapsulation
  - Polymorphism
  - Design patterns:
    - Creational pattern: Prototype
    - Creational pattern: Composite
    - Behavioral pattern: Template
- GDI+, CImg

## Configuration
1. Open file ``SVG3.sln`` by Visual Studio 2013 or later.
2. In the ``Solution Explorer``, right click to ``SVG3 -> Properties``. At ``C/C++`` section, click General, then add these directories to ``Additional Include Directories``:
   - Xml2Svg
   - Xml2Svg/src
   - Xmg2Svg/include
   - Xml2Svg/lib/rapidxml
   - Xmg2Svg/lib/Cimg
   - Xml2Svg/resources
3. Select ``Build -> Build Solution``
4. If build successful, select ``Debug -> Start Without Debugging`` to run the project.

## Demo
![](/docs/demo.gif)


