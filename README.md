# hex
## Hexagons for C++

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
