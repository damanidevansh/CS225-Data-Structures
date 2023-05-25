### Grade
Incomplete (0%)

Must resubmit!
### Comments
A well-written proposal overall but unfortunately you will need to resubmit it to include three valid algorithms.

**Leading Question**
The leading question of finding the shortest path between two airports is reasonable. However, you will have to replace either Floyd-Warshall or Dijktra's with a different algorithm which is 'uncovered' (see comments below). I would recommend modifying your leading question to encompass the new algorithm you choose. Also, note that BFS only finds the shortest path between two nodes in terms of edges traversed.

**Dataset**
The dataset is well described and the data correction procedure is very clear. There is a minor flaw in the data storage section, as you have given an estimate storage cost but you have not clearly mentioned what data structure you plan to use.

**Algorithm**
There is a minor flaw in your runtime for Dijkstra's, as the priority queue implementation is O((E + N)log(N)), not O(E + Nlog(N)). This appears like it may have just been a mistype on your part, however. 

Your description for Floyd-Warshall is good, but the main issue with your proposal (and the reason for an 'incomplete' grade) is that Floyd-Warshall and Dijkstra's are both considered 'covered' algorithms that perform the task of finding the shortest-path in a graph. As per the project requirements, at least one 'uncovered' algorithm must be implemented. As such, you will need to replace either Dijktra's or Floyd-Warshall with an 'uncovered' algorithm (please see the 'Project Goals' link from the final project webpage for more details).
