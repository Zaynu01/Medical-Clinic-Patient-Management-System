#include<stdio.h>
#include<string.h>
#define SIZE 10

typedef struct{

    char name[20];
    char phone_n[20];
    int priority_n;

}patient_info;

void menu(void){
  printf("\n\t\t---------------------Menu--------------------\n");
  printf("\n\t\t1.Start\n");
  printf("\n\t\t2.Add a new patient\n");
  printf("\n\t\t3.Print the list of patients\n");
  printf("\n\t\t4.Serve a patient\n");
  printf("\n\t\t5.Drop my visit\n");
  printf("\n\t\t6.Doctor visits OVER\n");
  printf("\n\t\t----------------------------------------------\n");
  printf("\n\t\tPlease make your choice: ");
}

int load_file_heap(FILE* infp, patient_info* heap){

    char line[50];
    int i = 0;

    fseek(infp, 0, 0);

    while(!feof(infp)){

        fgets(heap[i].name,20,infp);
        heap[i].name[strlen(heap[i].name)-1] = '\0';
        fgets(heap[i].phone_n,20,infp);
        heap[i].phone_n[strlen(heap[i].phone_n)-1] = '\0';
        heap[i].priority_n = 10; // since everyone has an appointment
        fgets(line, 50, infp); //read the seperation line

        i++;

        if(i == 10)
            break;

    }
    
    return (i);
}

void heapify(patient_info* heap, int parent_index, int last_index){
	
	int left_child, right_child, largest;
	//base case
	if(parent_index > ((last_index-1)/2))
	  return;
    else{

        left_child = (2*parent_index)+1;
        right_child = (2*parent_index)+2;
        
        if(right_child > last_index)
        largest = find_max(heap, parent_index, left_child);
        else
        {
            int left_max = find_max(heap, parent_index, left_child);
            int right_max = find_max(heap, parent_index, right_child);

            if (heap[right_max].priority_n > heap[left_max].priority_n) {
                largest = right_max;
            } else {
                largest = left_max;
            }

        }

        if(largest != parent_index){

        swap(&heap[parent_index], &heap[largest]);
        heapify(heap, largest, last_index); 

        } 

	}

}

int find_max(patient_info* arr, int i, int j){

  if(arr[i].priority_n > arr[j].priority_n)
    return(i);
  else
    return(j);

}

void swap(patient_info* a, patient_info* b){

 patient_info temp; 
  
  temp = *a;
  *a = *b;
  *b = temp;

}

int add_new_element_heap(patient_info* heap, patient_info Toadd, int*n_elements){
  int i_to_fill;
  //check if heap full
  if(*n_elements == SIZE)
    return -1;
  else{

    i_to_fill = (*n_elements)++;
    heap[i_to_fill] = Toadd;

    while(i_to_fill >= 1 && heap[i_to_fill].priority_n > heap[(i_to_fill-1)/2].priority_n){

      swap(&heap[i_to_fill], &heap[(i_to_fill-1)/2]);
      i_to_fill = (i_to_fill-1)/2;

    }

    return i_to_fill;

  }

}

patient_info get_patient_info(){

    patient_info patient;

    printf("\n\t\tEnter the name of the patient to add: ");
    gets(patient.name);
    printf("\n\t\tEnter the phone number of the patient: ");
    gets(patient.phone_n);
    printf("\n\t\tEnter the reason of the visit: ");
    printf("\n\t\t-------------------------------------");
    printf("\n\n\t\t0. A Friendly Visit\n\n\t\t5. A Medical Checkup\n\n\t\t10. An appointment\n\n\t\t15. An Emergency Case");
    printf("\n\t\t-------------------------------------");
    printf("\n\t\tYour choice: ");
    scanf("%d", &patient.priority_n);
    getchar();

    return patient;

}

patient_info delete_urgent_element(patient_info* heap, int* n_elements){

  patient_info urgent_element;
  int last_index;

  if(*n_elements == 0){

    urgent_element.priority_n = -1;
    return urgent_element;

  }
  else{

    urgent_element = heap[0];
    heap[0] = heap[--(*n_elements)];
    last_index = (*n_elements-1);// if there is one element in the heap

    if(last_index < 0)
      return heap[0];

    heapify(heap, 0, last_index);

    return(urgent_element);

  }

}

void heap_sort(patient_info* heap, int n_elements){
  //copy heap element to an array
  //apply delete ro array 2
  patient_info heap2[SIZE];
  patient_info element;
  //Back up the content of the heap to an array

  for(int i = 0; i < n_elements; i++)
    heap2[i] = heap[i];
  
  while(n_elements != 0 ){

    element = delete_urgent_element(heap2, &n_elements);
    printf("\n\t\t%s\t\t%s\t\t%d\n",element.name, element.phone_n, element.priority_n);

  }

  printf("\n");

}

int search_patient(patient_info* heap, patient_info patient, int n_elements){

  for(int i = 0; i < n_elements; i++){

    if(strcmp(heap[i].name, patient.name) == 0 && strcmp(heap[i].phone_n, patient.phone_n) == 0)
      return i;

  }

  return -1;

}

void delete_patient(patient_info* heap, int i, int* n_elements){

  swap(&heap[i], &heap[(*n_elements)-1]);

  (*n_elements)--;

  heapify(heap, i, *n_elements-1);  

}

void shift_over(patient_info* heap, int* n_elements){

  patient_info patient;
  FILE* outpf;

  while(*n_elements > 0 && heap[0].priority_n == 15)
    patient = delete_urgent_element(heap, &(*n_elements));

  if(*n_elements > 0)
    outpf = fopen("appointments.txt", "w");
  
  while(*n_elements > 0){

    patient = delete_urgent_element(heap, &(*n_elements));
    //Reset priority number to 10
    patient.priority_n = 10;
    fprintf(outpf, "%s\n%s\n%d\n", patient.name, patient.phone_n, patient.priority_n);
    fprintf(outpf, "--------------------------\n");

  }

  fclose(outpf);

}

int main(){
    
    FILE* infp;
    int choice, n_elements, flag, heap_loaded = 0;
    patient_info heap[SIZE];
    patient_info patient;

    do
    {
      menu();
      scanf("%d", &choice);
      getchar();

      if((choice > 1 && choice < 7) && (heap_loaded == 0))
        printf("\n\t\tYou need to load patients to the heap!\n");
      else{

        switch (choice){

          case 1:

            infp = fopen("patient.txt", "r");

            if (infp == NULL)
              printf("\n\t\tThe file does not exist!\n");
            else{

              if(heap_loaded == 0){

                n_elements = load_file_heap(infp, heap);
                printf("\n\t\tThe file was successfully loaded into the heap.\n");              
                heap_loaded = 1;

              }
              else
                printf("\n\t\tHeap was already loaded!");

                infp = freopen("patient.txt", "w", infp); // to clear the file data
                fclose(infp);

            }

            break;

          case 2:
                
            patient = get_patient_info();

            if(patient.priority_n != 0 && patient.priority_n != 5  && patient.priority_n != 10  && patient.priority_n != 15 ){
              printf("\n\t\tWrong Choice!");
              break;
            }
                    

            flag = add_new_element_heap(heap, patient, &n_elements);

            if(flag != -1)
              printf("\n\t\tThe patient %s was added successfully to the slot #%d", patient.name, flag+1);
            else
              printf("\n\t\tThe heap is full");

            break;

          case 3:
      
            heap_sort(heap, n_elements);

            break;

          case 4:

            patient = delete_urgent_element(heap, &n_elements);

            if(patient.priority_n == -1)
              printf("\n\t\tThe system is empty.");
            else
              printf("\n\t\tThe patient %s has been served.", patient.name);

            break;

          case 5:

            printf("\n\t\tEnter the patient Full Name: ");
            gets(patient.name);
            printf("\n\t\tEnter the patient's phone number: ");
            gets(patient.phone_n);

            flag = search_patient(heap, patient, n_elements);

            if(flag == -1)
              printf("\n\t\tThe patient %s with the phone number: %s, does not exist.", patient.name, patient.phone_n);
            else{
              delete_patient(heap, flag, &n_elements);
              printf("\n\t\tThe patient %s had successfully deleted.", patient.name);

              for(int i = 0; i < n_elements; i++){
                printf("\n\t\t%s\t\t%s\t\t%d\n",heap[i].name, heap[i].phone_n, heap[i].priority_n);
              }

            }
                
            break;

          case 6:

            shift_over(heap, &n_elements);

            break;

          default:
            printf("\n\t\tThat was a wrong choice!\n");

        }

      }     
      
    }while (choice != 6);

    return 0;
}