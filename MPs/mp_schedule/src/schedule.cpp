/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

using namespace std;

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */


V2D file_to_V2D(const std::string & filename){

  V2D output;
  string data = file_to_string(filename);
  vector<string> rowtemp;
  int x = SplitString(data,'\n', rowtemp);

  for(unsigned i = 0; i < rowtemp.size(); i ++){
    vector<string> rowstring;
    vector<string> rowstringfinal;
    int y =  SplitString(rowtemp[i], ',', rowstring);
    for(unsigned j = 0 ; j < rowstring.size(); j++){
      rowstringfinal.push_back(Trim(rowstring[j]));
    }
    output.push_back(rowstringfinal);
  }
    return output;

}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(V2D & cv, V2D & student){
  // YOUR CODE HERE
  // return V2D();
  // /*
  V2D result; 
  unsigned cvrowcount = cv.size();
  unsigned studentrowcount = student.size(); 

  for (unsigned i = 0; i < cvrowcount; i++) { 
  vector<string> rowvec;
  unsigned cvcolcount = cv[i].size();
    for (unsigned j = 1; j < cvcolcount; j++) { 
      for (unsigned a = 0; a < studentrowcount; a++) {
        if (student[a][0].compare(cv[i][j]) == 0) {
          unsigned studentcolcount = student[a].size();
          for (unsigned b = 1; b < studentcolcount; b++) {
            if (cv[i][0].compare(student[a][b])==0) { 
              rowvec.push_back(student[a][0]);
            }
          } 
        }
      } 
    } 
    if (rowvec.size() > 0){
      vector<string> finalrowvec;
      finalrowvec.push_back(cv[i][0]);
      while(rowvec.size() != 0){
         finalrowvec.push_back(rowvec[0]);
         rowvec.erase(rowvec.begin());
      }
      result.push_back(finalrowvec);
    }
  } 

  return result;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */

 V2D schedule(V2D courses, std::vector<std::string> timeslots){
    // Your code here!
    V2D output;
    vector<string> temp;
    temp.push_back("-1");
    output.push_back(temp);
    return output;
/*
  V2D course_results;
  vector<vector<int>> holdAdj;//matrix goes here
  vector<int> holdTime;//trial coloring
  int temp;
  int number = -1;
  

  holdAdj = graphHelper(courses);//create matrix
  
  //i
  //search starts at node 0
  //try starting at other positions up to holdtime size
  //put in new for loop to adjust definition of i 
  
  for(unsigned long k = 0; k < courses.size(); k++){
    holdTime.clear();
    
    for(unsigned long e = 0; e < courses.size(); e++){
      holdTime.push_back(-1);//-1 indicates empty
    }
    
    for(unsigned long m = 0; m < holdTime.size(); m++){
      unsigned long i = (m + k) % holdTime.size();//change start position of search
      temp = -1;//reset everytime we look for a new course
      
      for(unsigned long a = 0; a < timeslots.size(); a++){
        
        for(unsigned long j = 0; j < holdAdj[i].size(); j++){
          
          if(holdAdj[i][j] == 1 && i != j){//2 courses share student
          
            if(holdTime[j] == (int)a){
              temp = a;
              
              break;//break when we find a valid coloring
              
            }
          }
        }
        if(temp == -1){//break when we find a color
          temp = a;
          break;
        }else{
          temp = -1;
        }
      }
      holdTime[i] = temp;
    }
    number = checkColoring(holdAdj, holdTime, (int)timeslots.size());
    
    if(number != -1){
      break;
    }
  }
    
  
  

  if(number == -1){
    course_results.push_back(vector<string>());
    course_results[0].push_back("-1");
    return course_results;
  }

  for(unsigned long b = 0; b < timeslots.size(); b++){//set up results vector
    
    course_results.push_back(vector<string>());
    course_results[b].push_back(timeslots[b]);//insert time
    for(unsigned long c = 0; c < holdTime.size(); c++){
      if(holdTime[c] == (int)b){
        course_results[b].push_back(courses[c][0]);//insert course
      }
    }
  }
  
  
  
  return course_results;
*/
}

//Helpers

//checkColoring takes in our adjacency matrix - set up using given courses - and also a trial coloring of our matrix
//Also takes in the number of schedule slots we need to properly schedule each course
//and returns the chromatic number of our graph or if we don't have a valid coloring it returns -1
// int checkColoring(vector<vector<int>> holdAdj, vector<int> holdTime, int scheduleSlots){
//   vector<int> temp(scheduleSlots, 0);//store whether we've used a specific color - color count for a specific color
//   int chromatic = 0;

//   for(unsigned long i = 0; i < holdTime.size(); i++){

//     if(holdTime[i] == -1){//base case
//       return -1;//unscheduled class, return -1

//     }
//     temp[holdTime[i]] = temp[holdTime[i]] + 1;//Check how many times we've seen a color then add to color count

//   }
//   for(unsigned long j = 0; j < temp.size(); j++){
    
//     if( temp[j] != 0){
//       chromatic = chromatic + 1;
//     }
//   }
  
//   for(unsigned long i = 0; i < holdTime.size(); i++){
//     for(unsigned long j = 0; j < holdAdj[i].size(); j++){

//       if(holdAdj[i][j] == 1 && i != j){//2 courses share student
//         if(holdTime[i] == holdTime[j]){
//           return -1;
//         }
//       }

//     }
//   }  

//   return chromatic;//return when we have no unscheduled classes and when no adjacent nodes share the same color
// }


// //graphHelper takes in 2D vector cv containing course and course roster.
// //It returns an adjacency matrix of which courses have students in common - where rosters overlap
// //We can think of the matrix as a "course x course" matrix
// vector<vector<int>> graphHelper(V2D cv){
//   vector<vector<int>>adjGraph;

//   for(unsigned long i = 0; i < cv.size(); i++){//set up rows of adjGraph
//     adjGraph.push_back(vector<int>());
//     for(unsigned long j = 0; j < cv.size(); j++){//initiialize to 0
//       adjGraph[i].push_back(0);

//     }
//   }

//   for(unsigned long i = 0; i < adjGraph.size();i++){
//     for(unsigned long j = 0; j < adjGraph[i].size();j++){
//       for(unsigned long a = 1; a < cv[i].size(); a++){
//         for(unsigned long b = 1;  b < cv[j].size();b++){
//           if(i == j){
//             break;
//           }
//           if(cv[i][a] == cv[j][b]){
//             adjGraph[i][j] = 1;
//           }
//         }   
//       }
//     }
//   }

//   return adjGraph;
// }