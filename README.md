# TravelingSalesman

The problem is that we have a salesman who travels around sixteen provincial capitals in Poland. He needs to travel through all af them, but choosing a city randomly is not efficient. We need to find a way to travel the shortest distance. After visiting every city, he gets back to the city he started in.

## Explanation

To make this problem a little bit easier to understand, let's take four cities as an example. Distance betweeen city:
<ul><li>A and B = 5;</li>
 <li>A and C = 10;</li>
 <li>A and D = 8;</li>
 <li>B and C = 20;</li>
 <li>B and D = 14;</li>
 <li>C and D = 6</li></ul>
 
Let's put this in an array to make it clearer:
 
||**A**|**B**|**C**|**D**|
|-|-|-|-|-|
|**A**|0|5|10|8|
|**B**|5|0|20|14|
|**C**|10|20|0|6|
|**D**|8|14|6|0|

To make sure we found the shortest distance, we need to check every possible path. In case of four cities there would be 24 possible paths:
<ol>
 <li>A &rarr; B &rarr; C &rarr; D &rarr; A = 39</li>
 <li>A &rarr; B &rarr; D &rarr; C &rarr; A = 35</li>
 <li>A &rarr; C &rarr; B &rarr; D &rarr; A = 52</li>
 <li>A &rarr; C &rarr; D &rarr; B &rarr; A = 35</li>
 <li>A &rarr; D &rarr; B &rarr; C &rarr; A = 52</li>
 <li>A &rarr; D &rarr; C &rarr; B &rarr; A = 39</li>
 <li>B &rarr; A &rarr; C &rarr; D &rarr; B = 35</li>
 <li>B &rarr; A &rarr; D &rarr; C &rarr; B = 39</li>
 <li>B &rarr; C &rarr; A &rarr; D &rarr; B = 52</li>
 <li>B &rarr; C &rarr; D &rarr; A &rarr; B = 39</li>
 <li>B &rarr; D &rarr; A &rarr; C &rarr; B = 52</li>
 <li>B &rarr; D &rarr; C &rarr; A &rarr; B = 35</li>
 <li>C &rarr; A &rarr; B &rarr; D &rarr; C = 35</li>
 <li>C &rarr; A &rarr; D &rarr; B &rarr; C = 52</li>
 <li>C &rarr; B &rarr; A &rarr; D &rarr; C = 39</li>
 <li>C &rarr; B &rarr; D &rarr; A &rarr; C = 52</li>
 <li>C &rarr; D &rarr; A &rarr; B &rarr; C = 39</li>
 <li>C &rarr; D &rarr; B &rarr; A &rarr; C = 35</li>
 <li>D &rarr; A &rarr; B &rarr; C &rarr; D = 39</li>
 <li>D &rarr; A &rarr; C &rarr; B &rarr; D = 52</li>
 <li>D &rarr; B &rarr; A &rarr; C &rarr; D = 35</li>
 <li>D &rarr; B &rarr; C &rarr; A &rarr; D = 52</li>
 <li>D &rarr; C &rarr; A &rarr; B &rarr; D = 35</li>
 <li>D &rarr; C &rarr; B &rarr; A &rarr; D = 39</li>
 </ol>
 
As we can see, there are multiple correct answers. Still, we needed to check every possible path to be sure, when done by hand it took quite a while. If we were to check every posibility with sixteen cities, it would took hours if not days.

There are however optimisations we can make. For example, salesman probably lives in on near one of those cities, so letting them choose a starting point would be great idea. It significantly cuts checks to make.

Calculations does not need to be perfect. Most of the times, finding lowest distance to the next city gives great results. For example, assume we start in city A. The shortest distance is to the city A (0), however we can't travel to the same city we are already in. The shortest distance is to the city B (5), so we travel there. Our current path is **A &rarr; B = 5**. The shortest distance is to the city B (0), but we are currently here, next to the city A (5), however we already been there and there is more cities to visit. So we travel to city D (14). Our current path is **A &rarr; B &rarr; D = 19**. Form the city D we can't travel to D (we are currently here), A (there is still one more city to visit) or B (we've been there already). The only possible way is to the city C (6). Our current path is **A &rarr; B &rarr; D &rarr; C = 25**. Since we visited every possible city, we need to return to the city we started from – city A (10). Our final path is **A &rarr; B &rarr; D &rarr; C &rarr; A = 35**.

I took those optimisations into consideration while coding and I believe resulst are quite good.

Thank you for coming to my TED Talk :satisfied:
