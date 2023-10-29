#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKINGS 50

struct Booking {
    char name[50];
    int seat_number;
};

struct Movie {
    char title[100];
    int available_seats;
    struct Booking bookings[MAX_BOOKINGS];
};

void initializeMovie(struct Movie *movie, const char *title, int total_seats) {
    strcpy(movie->title, title);
    movie->available_seats = total_seats;
    for (int i = 0; i < MAX_BOOKINGS; i++) {
        movie->bookings[i].seat_number = 0;
    }
}

void bookTicket(struct Movie *movie, const char *name) {
    if (movie->available_seats <= 0) {
        printf("Sorry, all seats for %s are booked.\n", movie->title);
    } else {
        int seat_number = -1;
        for (int i = 0; i < MAX_BOOKINGS; i++) {
            if (movie->bookings[i].seat_number == 0) {
                seat_number = i + 1;
                strcpy(movie->bookings[i].name, name);
                movie->bookings[i].seat_number = seat_number;
                break;
            }
        }
        if (seat_number != -1) {
            movie->available_seats--;
            printf("Booking successful! Your seat number is %d.\n", seat_number);
        } else {
            printf("Booking failed. Please try again later.\n");
        }
    }
}

void cancelTicket(struct Movie *movie, int seat_number) {
    if (seat_number >= 1 && seat_number <= MAX_BOOKINGS && movie->bookings[seat_number - 1].seat_number != 0) {
        movie->bookings[seat_number - 1].seat_number = 0;
        movie->available_seats++;
        printf("Booking for seat %d is canceled.\n", seat_number);
    } else {
        printf("Invalid seat number or no booking found.\n");
    }
}

void viewBookings(struct Movie *movie) {
    printf("Movie: %s\n", movie->title);
    printf("Available Seats: %d\n", movie->available_seats);
    printf("Booking Records:\n");
    for (int i = 0; i < MAX_BOOKINGS; i++) {
        if (movie->bookings[i].seat_number != 0) {
            printf("Seat %d: %s\n", movie->bookings[i].seat_number, movie->bookings[i].name);
        }
    }
}

int main() {
    struct Movie movie;
    initializeMovie(&movie, "Avengers: Endgame", 50);

    while (1) {
        printf("\nMovie Booking System\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. View Bookings\n");
        printf("4. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50];
                printf("Enter your name: ");
                scanf("%s", name);
                bookTicket(&movie, name);
                break;
            }
            case 2: {
                int seat_number;
                printf("Enter seat number to cancel: ");
                scanf("%d", &seat_number);
                cancelTicket(&movie, seat_number);
                break;
            }
            case 3:
                viewBookings(&movie);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
