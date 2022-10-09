# TravelingSalesman

The problem is that we have a salesman who travels around sixteen provincial capitals in Poland. He needs to travel through all af them, but choosing a city randomly is not efficient. We need to find a way to travel the shortest distance.

To make this problem a little bit easier to understand, let's take four cities as an example. Distance betweeen city:
<ul><li>A and B = 5;</li>
 <li>A and C = 10;</li>
 <li>A and D = 8;</li>
 <li>B and C = 20;</li>
 <li>B and D = 14;</li>
 <li>C and D = 6</li>
 
Let's put this in an array to make it clearer:
 
||A|B|C|D|
|-|-|-|-|-|
|A|0|5|10|8|
|B|5|0|20|14|
|C|10|20|0|6|
|D|8|14|6|0|
