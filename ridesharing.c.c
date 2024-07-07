#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define BASE_FARE 50 
#define FARE_PER_KM 60

struct Location {
    float latitude;
    float longitude;
};

struct driver
{
    char name[30];
    char car_details[40];
    int availability;       // 0 for occupied, 1 for free
    struct driver *next;
    struct Location location;
};

struct passenger
{
    char name[30];
    struct passenger *next;
    struct Location location;
};

struct ride
{
    char name_P[30];
    char car_details[40];
    struct ride* next;
    int status;  // 0 for Pending, 1 for Completed, -1 for cancelled
    struct Location current;
    struct Location destination;
};

double distance(struct Location l1, struct Location l2) // calculates distance between two points using distance formula
{
     return sqrt(pow(l1.latitude - l2.latitude, 2) + pow(l1.longitude - l2.longitude, 2));
}

void calculateFare(struct Location l1, struct Location l2)  // calculates the total fare
{
    double totalFare;
    double dist = distance(l1, l2);
    if (dist < 1.0) {
        totalFare = 50.0;
    }
    else
    {
        dist = dist - 1;
        totalFare = BASE_FARE + FARE_PER_KM * dist;
    }

    printf("TOTALFARE : %lf\n", totalFare);
}

void completeride(struct ride* head_R,struct driver* head_D) 
{
    int flag = 0;
    char car_detailscopy[40];
    printf("car_details: ");
    fflush(stdin);
    scanf("%s", car_detailscopy);
    struct ride* temp = head_R;
    struct driver* temp1 = head_D;
    while(temp != NULL)
    {
        if((strcmp(car_detailscopy,temp -> car_details) == 0) && (temp -> status == 0)) // checks whether the car details are present and the status is zero(pending)
        {       
            temp -> status = 1;
            flag = 1;
			printf("Ride Completed ! \n");
            break;
        }
        temp = temp -> next;
    }
    while(temp1 != NULL)
    {
        if(strcmp(car_detailscopy,temp1 -> car_details) == 0) // it updates the availability of the ride
        {
            temp1 -> availability = 1;
            temp1 -> location = temp -> destination; 
            calculateFare(temp -> current, temp -> destination);
            break;
        }
        temp1 = temp1 -> next;
    }
    if(flag == 0)
    {
        printf("Entered incorrect car_details\n"); 
    }
}

void cancelride(struct ride* head_R, struct driver* head_D)
{
    int flag = 0;
    char car_detailscopy[40];
    printf("car_details: ");
    fflush(stdin);
    scanf("%s", car_detailscopy);
    struct ride* temp = head_R;
    struct driver* temp1 = head_D;
    while(temp != NULL)
    {
        if((strcmp(car_detailscopy,temp -> car_details) == 0) && (temp -> status == 0)) // checks whether the car details are present and the status is zero(pending)
        {
            temp -> status = -1;
            flag = 1; 
            printf("Ride cancelled !\n");
            break;
        }
        temp = temp -> next;
    }
    while(temp1 != NULL)
    {
        if(strcmp(car_detailscopy,temp1 -> car_details) == 0) // updates availability of ride
        {
            temp1 -> availability = 1;
           
            break;
        }
        temp1 = temp1 -> next;
    }
    if(flag == 0)
    {
        printf("Entered incorrect car_details\n");
    }
}

int check(struct passenger *head_P, char name[])// checking whether the passenger is alredy added into our data
{
    struct passenger *temp = head_P;
    while(temp != NULL)
    {
        if(strcmp(temp -> name, name) == 0)
        {
            return 1;
        }
        temp = temp -> next;
    }
    return 0;
}

struct ride *addRide(struct ride *head_R, struct driver *head_D, struct passenger *head_P)
{ 
    int count = 0;
    double minDist, dist;
    struct driver *d, *temp_D = head_D;
    struct ride *temp_R = head_R;
    struct ride *newnode= (struct ride *)malloc(sizeof(struct ride));
    newnode -> next = NULL;
    printf("Passenger Name: ");
    fflush(stdin);
    scanf("%s", newnode->name_P);
    if(check(head_P, newnode->name_P) == 0)// handling condition where passenger doesn't exist
    {
        printf("Passenger doesn't exist\n");
        return head_R;
    }
    while(temp_R != NULL) // checking if the passenger has a pending ride
    {
        if((strcmp(temp_R -> name_P, newnode -> name_P) == 0) && (temp_R -> status == 0))
        {
            count++;
        }
        temp_R = temp_R -> next;
    }
    if(count != 0)
    {
        printf("Passenger has a ride pending\n");
        return head_R;
    }
    
    printf("Enter current location:\n");
    printf("Latitude: ");
    scanf("%f", &(newnode -> current.latitude));
    printf("Longitude: ");
    scanf("%f", &(newnode -> current.longitude));
    printf("Enter destination location:\n");
    printf("Latitude: ");
    scanf("%f", &(newnode -> destination.latitude));
    printf("Longitude: ");
    scanf("%f", &(newnode -> destination.longitude));
    
    minDist = distance(newnode -> current, temp_D -> location);
    
    d = temp_D;
    temp_D = temp_D -> next;
    while(temp_D != NULL) // getting pointer to driver who is at a minimum distance from the passenger
    {
        dist = distance(newnode -> current, temp_D -> location);
        if( (dist < minDist) && (temp_D -> availability == 1))
        {
            d = temp_D;
            minDist = dist;
        }
        temp_D = temp_D -> next;
    }
    
    if(d -> availability != 1) 
    {
        printf("No drivers available\n");
        return head_R;
    }
    
    if(head_R != NULL){
        newnode->next = head_R;
    }
    newnode -> status = 0;
    strcpy(newnode -> car_details, d -> car_details);
    d -> location = newnode -> current;
    d -> availability = 0;
      
    printf("Booking completed\n");
    printf("Driver: %s\n", d -> name);
    printf("Car Details: %s\n", d -> car_details);
    
    return newnode;
    
}

struct driver* addDriver(struct driver *head_D)
{
    struct driver *newnode = (struct driver *)malloc(sizeof(struct driver));
    printf("Name: ");
    fflush(stdin);
    scanf("%s", newnode -> name);
    
    printf("car_details: ");
    fflush(stdin);
    scanf("%s", newnode -> car_details);
    
    newnode -> availability = 1;
    
    printf("Latitude: ");
    scanf("%f", &(newnode -> location.latitude));
    
    printf("Longitude: ");
    scanf("%f", &(newnode->location.longitude));
    
    newnode -> next = NULL;
    if(head_D != NULL){
        newnode->next = head_D;
    }
    return newnode;
}

struct passenger *addPassenger(struct passenger *head_P)
{
    struct passenger *newnode= (struct passenger *)malloc(sizeof(struct passenger));
    printf("Name: ");
    fflush(stdin);
    scanf("%s", newnode->name);
    
    printf("Latitude: ");
    scanf("%f", &(newnode -> location.latitude));
    
    printf("Longitude: ");
    scanf("%f", &(newnode->location.longitude));
    
    newnode -> next = NULL;
    if(head_P != NULL){
        newnode->next = head_P;
    }
    return newnode;
}

int main() 
{
    struct driver *head_D = NULL;
    struct passenger *head_P = NULL;
    struct ride *temp_R, *head_R = NULL;
    char name_P [30];
    char car_details [40];
    int choice = 1;
    while(choice)
    {
        printf("\n************************************************************************************\n");
        printf(" 0.Exit \n 1.Add a Driver \n 2.Add a Passenger \n 3.Request a Ride \n 4.Complete a Ride \n 5.Cancel a Ride \n 6.Calculate Ride Fare \n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 0:
                    break;
            case 1: 
                    head_D = addDriver(head_D);
                    break;
            case 2: 
                    head_P = addPassenger(head_P);
                    break;
            case 3:
                    if(head_D == NULL)
                    {
                        printf("No Drivers\n");
                    }
                    head_R = addRide(head_R, head_D, head_P);
                    break;
                
            case 4:
                    completeride(head_R, head_D);
                    break;
            case 5:
                    cancelride(head_R, head_D);
                    break;
            case 6:
                    printf("Passenger Name: ");
                    fflush(stdin);
                    scanf("%s", name_P);

                    printf("car_details: ");
                    fflush(stdin);
                    scanf("%s", car_details);
                    temp_R = head_R;
                    while(temp_R != NULL)
                    {
                        if((strcmp(temp_R -> name_P, name_P) == 0) && (strcmp(temp_R -> car_details, car_details) == 0))
                        {
                            calculateFare(temp_R -> current, temp_R -> destination);
                            break;
                        }
                        temp_R = temp_R -> next;
                    }
                    break;
                default:
                    printf("Invalid Input\n");
                    break;
        }
    }
    return 0;
}