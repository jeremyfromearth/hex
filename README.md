# __HEX__
## Hexagonal grids for C++
This library provides only hexagon related computations and is renderer agnostic. The examples below have been rendered using [Cinder](http://libcinder.org).

### Creation, addition & subtraction
```
l = hex::layout::hexagonal(6);
```
![demo 1](images/demo-1.png)
```
l -= hex::layout::hexagonal(3);
```
![demo 2](images/demo-2.png)
```
l += hex::layout::parallelogram(10, 10, layout::options::vertical);
```
![demo 3](images/demo-3.png)
```
l += hex::layout::parallelogram(10, 10, layout::options::standard);
```
![demo 4](images/demo-4.png)
```
l -= hex::layout::hexagonal(3);
```
![demo 5](images/demo-5.png)
```
l += hex::layout::hexagonal(1);
```
![demo 6](images/demo-6.png)

### Coordinate space conversions

```
vec2 v = vec2(e.getPos()) - getWindowCenter();
hex::point p(v.x, v.y);
hover = hex::lattice::point_to_cell(p, orientation, radius);
```
![demo 7](images/pixel-to-hex-and-neighbors.gif)

### References
Red Blob Games: http://www.redblobgames.com/grids/hexagons/
