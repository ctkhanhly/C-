// But first we want to get something working in a single file, 
// no separate compilation and no namespaces. 
// Here we are not reading a file, 
// instead just using local calls to the Registrar's methods 
// to add students and courses, etc. We are not even implementing 
// all of the possible functionality. For example, we will 
// leave out dropping courses, students changing names, etc.


// We are assuming that names are unique 
// (if they weren't we would have to turn everyone into a number). 
// Remember, just because we occasionaly make such assumptions, 
// you should never assume names are unique unless your spec says so. 
// I have notiece that there is more than one person with the name 
// "John" in the real world.

// Where do you think the Course and Student objects should live? 
// Suppose you just kept a vector of them, why might that prove to be a disaster? 
// You are going to have pointers from a Course to the Students. 
// If the Students are in a vector, i.e. a vector<Student>, 
// what might happen to their addresses with you push_back another Student? 
// If the vector was full, then the underlying array would get reallocated and 
// all the pointers to them would become invalid.

// Note that we are not asking you for copy control, despite the fact that the Registrar really owns all those objects on the heap.

// Probably writing the code that looks for the course or student by name would make a useful method.