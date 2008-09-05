
	#include    <unistd.h>
	#include	<iostream>
	#include <sys/wait.h>

	using namespace std;

	int main(){
	pid_t id;
	id=fork();
	cout<<id;
	if(id==0){
		cout<<"hello";
		execlp("firefox", '\0');
	//	cout<<"hello";
	}
	int *status;
	waitpid(id,status,WUNTRACED);
	return 0;
}
