#include "functions.h"
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

struct User users[100];
int userCount = 0;

void printfMenu(){
    printf("*** He Thong Quan Ly Ngan Hang Bang C ***\n");
    printf("====================================\n");
    printf("[1] Quan Tri.\n");
    printf("[2] Nguoi Dung.\n");
    printf("[0] Thoat Khoi Chuong Trinh.\n");
    printf("====================================\n");
}

void adminMenu(){
    int luaChon;
    do{
    	system("cls");
        printf("\n*** He Thong Quan Ly Ngan Hang Bang C ***\n");
        printf("====================================\n");
        printf("[1] Them Nguoi Dung Moi.\n");
        printf("[2] Hien Thi Tat Ca Nguoi Dung.\n");
        printf("[3] Hien Thi Chi Tiet Nguoi Dung.\n");
        printf("[4] Khoa (Mo Khoa) Nguoi Dung.\n");
		printf("[5] Sap Xep Nguoi Dung.\n");
        printf("[0] Thoat Khoi Chuong Trinh.\n");
        printf("====================================\n");
        printf("Nhap Lua Chon: ");
        scanf("%d", &luaChon);
        getchar();

        switch(luaChon){
            case 1:
                addNewUser();
                break;
            case 2:
                showAllUsers();
                break;
            case 3:
                showUserDetail();
                break;
            case 4:
                lockUnlockUser();
                break;
            case 5:
                sortUser();
                break;
            case 0:
                printf("====== Cam On =====\n====== Hen Gap Lai ====\n");
                exit(0);
            break;
            default:
                printf("Lua Chon Khong Hop Le.\n");
            	exit(0);
        }
    }while(1);
}

//Function Add Users
void addNewUser(){
    system("cls");
    if(userCount >= 100){
        printf("Loi: Khong The Them Nguoi Dung. Da Het So Duong Danh Sach.\n");
    return;
    }

    struct User newUser;
    struct AccountInfo newAccount;
    char choice;
    printf("*** Them Nguoi Dung Moi ***\n");
	loadFile();
	
	//ID/CCCD
    do{
        printf("Nhap ID/CCCD (Chinh Xac 10 Ky Tu): ");
        scanf("%s", &newUser.userId);
        
        int validCheck = 0;
        int i;
        for(i = 0; i < userCount; i++){
            if(strcmp(users[i].userId, newUser.userId) == 0){
                validCheck = 1;
            break;
            }
        }
        
    	if(strlen(newUser.userId) != 10){
        	printf("Loi: ID/CCCD Phai Co Chinh Xac 10 Ky Tu.\n");
        	continue;
    	}
		
        if(validCheck){
            printf("Loi: ID/CCCD Da Ton Tai.\n");
        }else{
            break;
        }
    }while(1);

	//Name
	do{
    	printf("Nhap Ten: ");
    	getchar();
    	fgets(newUser.name, sizeof(newUser.name), stdin);
    	newUser.name[strcspn(newUser.name, "\n")] = 0;
        
        int validNumber;
        validNumber = 1; //1: Trang Thai Luon Dung
        int i;
        for(i = 0; newUser.name[i] != '\0'; i++){
            if(isdigit(newUser.name[i])){
                validNumber = 0;
            break;
            }
        }

        if(!validNumber){
            printf("Loi: Ten Khong Hop Le!\n");
        }else{
            break;
        }
    }while(1);

	//Email
    do{
        printf("Nhap Email: ");
        scanf("%s", &newUser.email);
        
        int validCheck = 0;
        int i;
        for(i = 0; i < userCount; i++){
            if(strcmp(users[i].email, newUser.email) == 0){
                validCheck = 1;
            break;
            }
        }
        
    	if(strlen(newUser.email) >= 30){
        	printf("Loi: Email Phai Nho Hon 30 Ki Tu.\n");
        	continue;
    	}
		
        if(validCheck){
            printf("Loi: Email Da Ton Tai.\n");
        }else{
            break;
        }
    }while(1);

	//Phone Number
	do{
        printf("Nhap So Dien Thoai (Chinh Xac 10 Ky Tu): ");
        scanf("%s", &newUser.userPhone);
        
        int validCheck = 0;
        int i;
        for(i = 0; i < userCount; i++){
            if(strcmp(users[i].userId, newUser.userPhone) == 0){
                validCheck = 1;
            break;
            }
        }
        
        int isValidPhone = 1;
    	for(i = 0; i < strlen(newUser.userPhone); i++){
        if(newUser.userPhone[i] < '0' || newUser.userPhone[i] > '9'){
            isValidPhone = 0;
            break;
       	 	}
    	}
    	if(!isValidPhone){
        	printf("Loi: So Dien Thoai Chi Duoc Chua So.\n");
        	continue;
    	}
    
    	if(strlen(newUser.userPhone) != 10){
        	printf("Loi: So Dien Thoai Phai Co Chinh Xac 10 Ky Tu.\n");
        	continue;
    	}
		
        if(validCheck){
            printf("Loi: So Dien Thoai Da Ton Tai.\n");
        }else{
            break;
        }
    }while(1);

    printf("Nhap Gioi Tinh (0 Cho Nu, 1 Cho Nam): ");
    scanf("%d", &newUser.gender);

	printf("Nhap Ngay Thang Nam Sinh:\n");
	int validDate = 0;
	while(!validDate){
    printf("Nhap Ngay: ");
    scanf("%d", &newUser.dateOfBirth.day);
    
    printf("Nhap Thang: ");
    scanf("%d", &newUser.dateOfBirth.month);

    printf("Nhap Nam: ");
    scanf("%d", &newUser.dateOfBirth.year);

    if(newUser.dateOfBirth.month < 1 || newUser.dateOfBirth.month > 12){
        printf("Thang Khong Hop Le!\n");
    continue;
    }
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if((newUser.dateOfBirth.year % 4 == 0 && newUser.dateOfBirth.year % 100 != 0) || (newUser.dateOfBirth.year % 400 == 0)){
        daysInMonth[1] = 29;
    }
    
    if(newUser.dateOfBirth.day < 1 || newUser.dateOfBirth.day > daysInMonth[newUser.dateOfBirth.month - 1]){
        printf("Ngay Khong Hop Le!\n", daysInMonth[newUser.dateOfBirth.month - 1]);
    continue;
    }
    validDate = 1;
	}

    do{
        printf("Nhap Ten Dang Nhap (Cho Tai Khoan): ");
        scanf("%s", &newAccount.userId);

        int checkTonTai = 0;
		int i;
        for(i = 0; i < userCount; i++){
            if(strcmp(users[i].account.userId, newAccount.userId) == 0){
                checkTonTai = 1;
                break;
            }
        }
        
        if(strlen(newAccount.userId) >= 20){
        	printf("Loi: Ten Dang Nhap Phai Nho Hon 20 Ki Tu.\n");
        	continue;
    	}

        if(checkTonTai){
            printf("Loi: Ten Dang Nhap Da Ton Tai.\n");
        }else{
            break;
        }
    }while(1);
    
    newAccount.balance = 0;

    newAccount.status = true;

    newUser.account = newAccount;

    users[userCount] = newUser;
    userCount++;
    saveFile();

    printf("\nNguoi Dung Da Duoc Them Thanh Cong!\n");

    do{
        printf("Quay Lai (b) Hoac Thoat (0)? : ");
        scanf(" %c", &choice);
        if(choice == 'b'){
            break;
        }else if (choice == '0'){
            printf("====== Cam On =====\n====== Hen Gap Lai ====\n");
            exit(0);
        }else{
            printf("Lua Chon Khong Hop Le. Vui Long Nhap 'b' De Quay Lai Hoac '0' De Thoat.\n");
        }
    }while(choice != 'b' && choice != '0');
}

//Function To Show All Users
void showAllUsers(){
    loadFile();
    system("cls");
    if(userCount == 0){
        printf("Khong Tim Thay Nguoi Dung.\n");
        return;
    }
    printf("|=====================|======================|============================|=================|=============|\n");
    printf("| ID/CCCD             | Ten Nguoi Dung       | Email                      | So Dien Thoai   | Trang Thai  |\n");
    printf("|=====================|======================|============================|=================|=============|\n");
    int i;
    for(i = 0; i < userCount; i++){
        struct User user = users[i];
        char status[10];
        strcpy(status, user.account.status ? "Hoat Dong" : "Khoa");
        printf("| %-19s | %-20s | %-26s | %-15s | %-11s |\n", user.userId, user.name, user.email, user.userPhone, status);
        printf("|=====================|======================|============================|=================|=============|\n");
    }
    
    char choice;
    do{
        printf("Quay Lai(b)? Hoac Thoat(0)?: ");
        scanf(" %c", &choice);
        if(choice == 'b'){
            return;
        }else if (choice == '0'){
            printf("====== Cam On =====\n====== Hen Gap Lai ====\n");
            exit(0);
        }else{
            printf("Lua Chon Khong Hop Le. Vui Long Nhap 'b' De Quay Lai Hoac '0' De Thoat.\n");
        }
    }while(1);
}

//Function To Show User Detail By Name or ID
void showUserDetail(){
    char searchTerm[50];
    int found = 0;
    int searchChoice;
    system("cls");
    loadFile();

    do{
        printf("Chon Lua Chon Tim Kiem:\n");
        printf("[1] Tim Kiem Theo Ma Nguoi Dung (CCCD)\n");
        printf("[2] Tim Kiem Theo Ten\n");
        printf("[3] Quay Lai\n");
        printf("Nhap Lua Chon (1 Hoac 2 Hoac 3): ");
        scanf("%d", &searchChoice);
        getchar();

        if(searchChoice == 1 || searchChoice == 2){
            break;
        }else if(searchChoice == 3){
            adminMenu();
        }else{
            printf("Lua Chon Khong Hop Le. Vui Long Nhap 1 Hoac 2 Hoac 3.\n");
        }
    }while(1);

    if(searchChoice == 1){
        printf("Nhap Ma Nguoi Dung (CCCD) Can Tim: ");
        fgets(searchTerm, sizeof(searchTerm), stdin);
        searchTerm[strcspn(searchTerm, "\n")] = '\0';
    }else if (searchChoice == 2){
        printf("Nhap Ten Nguoi Dung Can Tim: ");
        fgets(searchTerm, sizeof(searchTerm), stdin);
        searchTerm[strcspn(searchTerm, "\n")] = '\0';
    }
    printf("|============================================================================================================================|\n");
    printf("| ID/CCCD       | Ten Nguoi Dung     | Email                          | So Dien Thoai  | Gioi Tinh | Trang Thai | Ngay Sinh  |\n");
    printf("|============================================================================================================================|\n");

    int i;
    for(i = 0; i < userCount; i++){
        if(searchChoice == 1 && strcmp(users[i].userId, searchTerm) == 0){
            found = 1;
            char status[10];
            strcpy(status, users[i].account.status ? "Hoat Dong" : "Khoa");
            
            const char *gender = users[i].gender == 0 ? "Nu" : "Nam";

            printf("| %-13s | %-18s | %-30s | %-14s | %-9s | %-10s | %02d-%02d-%04d |\n", 
                   users[i].userId, users[i].name, users[i].email, users[i].userPhone, gender, status, 
                   users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year);
            printf("|============================================================================================================================|\n");
        }else if (searchChoice == 2 && strstr(users[i].name, searchTerm) != NULL){
            found = 1;
            char status[10];
            strcpy(status, users[i].account.status ? "Hoat Dong" : "Khoa");

            const char *gender = users[i].gender == 0 ? "Nu" : "Nam";
            
            printf("| %-13s | %-18s | %-30s | %-14s | %-9s | %-10s | %02d-%02d-%04d |\n", 
                   users[i].userId, users[i].name, users[i].email, users[i].userPhone, gender, status, 
                   users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year);
            printf("|============================================================================================================================|\n");
        }
    }
    if(!found){
        printf("Khong Tim Thay Nguoi Dung Khop.\n");
    }
    char choice;
    do{
        printf("Quay Lai (b)? Hoac Thoat (0)?: ");
        scanf(" %c", &choice);
        if (choice == 'b'){
            return;
        }else if (choice == '0'){
            printf("====== Cam On =====\n====== Hen Gap Lai ====\n");
            exit(0);
        }else{
            printf("Lua Chon Khong Hop Le. Vui Long Nhap 'b' De Quay Lai Hoac '0' De Thoat.\n");
        }
    }while(1);
}

//Functions Lock/Unlock User
void lockUnlockUser(){
    system("cls");
    char userId[10];
    int found = 0;
    loadFile();
    
    printf("Nhap Ma Nguoi Dung (CCCD): ");
    scanf("%s", userId);
    int i;
    for(i = 0; i < userCount; i++){
        if(strcmp(users[i].userId, userId) == 0){
            found = 1;
            if(users[i].account.status){
                printf("Tai Khoan Dang Hoat Dong. Ban Muon Khoa? (y/n): ");
            }else{
                printf("Tai Khoan Dang Bi Khoa. Ban Muon Mo Khoa? (y/n): ");
            }

            char choice;
            scanf(" %c", &choice);
            if(choice == 'y' || choice == 'Y'){
                users[i].account.status = !users[i].account.status;
                printf("Thao Tac Mo/Khoa Thanh Cong.\n");
            }else{
                printf("Loi: Khong Thuc Hien.\n");
            }
            saveFile(); 
        }
    }

    if(!found){
        printf("Loi: Khong Tim Thay Ma Nguoi Dung/CCCD.\n");
    }
    
    char choice;
    do{
        printf("Quay Lai (b)? Hoac Thoat (0)?: ");
        scanf(" %c", &choice);
        if (choice == 'b'){
            return;
        }else if (choice == '0'){
            printf("====== Cam On =====\n====== Hen Gap Lai ====\n");
            exit(0);
        }else{
            printf("Lua Chon Khong Hop Le. Vui Long Nhap 'b' De Quay Lai Hoac '0' De Thoat.\n");
        }
    }while(1);
}

//Functions Sort User
void sortUser(){
    system("cls");
    loadFile();

    if(userCount == 0){
        printf("Loi: Khong Co Nguoi Dung.\n");
        return;
    }

    int sortChoice;
    do{
    	printf("Chon Loai Sap Xep:\n");
    	printf("1. Tang Dan (A -> Z)\n");
   		printf("2. Giam Dan (Z -> A)\n");
    	printf("3. Quay Lai\n");
    	printf("Nhap Lua Chon Cua Ban (1 Hoac 2 Hoac 3): ");
    	scanf("%d", &sortChoice);
        getchar();

        if(sortChoice == 1 || sortChoice == 2){
            break;
        }else if(sortChoice == 3){
            adminMenu();
        }else{
            printf("Lua Chon Khong Hop Le. Vui Long Nhap 1 Hoac 2 Hoac 3.\n");
        }
    }while(1);

    int i;
    for(i = 0; i < userCount - 1; i++){
        int j;
        for(j = 0; j < userCount - 1 - i; j++){
            int compareResult = strcmp(users[j].name, users[j + 1].name);
            if((sortChoice == 1 && compareResult > 0) || (sortChoice == 2 && compareResult < 0)){
                struct User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
    printf("|=====================|========================|============================|=================|=============|\n");
    printf("|       ID/CCCD       |        Tên             |          Email             |  So Dien Thoai  | Trang Thai  |\n");
    printf("|=====================|========================|============================|=================|=============|\n");

    for (i = 0; i < userCount; i++) {
        struct User user = users[i];
        char status[10];
        strcpy(status, user.account.status ? "Hoat Dong" : "Khoa");

        printf("| %-19s | %-22s | %-26s | %-15s | %-11s |\n",
               user.userId, user.name, user.email, user.userPhone, status);
        printf("|=====================|========================|============================|=================|=============|\n");
    }

    char choice;
    do{
        printf("Quay Lai(b)? Hoac Thoat(0)?: ");
        scanf(" %c", &choice);
        if(choice == 'b'){
            return;
        }else if (choice == '0'){
            printf("====== Cam On =====\n====== Hen Gap Lai ====\n");
            exit(0);
        }else{
            printf("Lua Chon Khong Hop Le. Vui Long Nhap 'b' De Quay Lai Hoac '0' De Thoat.\n");
        }
    }while(1);
}

//Functions Load File .bin
void loadFile(){
    FILE *file = fopen("userData.bin", "rb");
    if(file == NULL){
        printf("No Saved User Data Found.\n");
        return;
    }
    fread(&userCount, sizeof(int), 1, file); 
    fread(users, sizeof(struct User), userCount, file);
    fclose(file);
    //printf("Loaded Successfully.\n");
}

//Functions Save File .bin
void saveFile(){
    FILE *file = fopen("userData.bin", "wb");
    if(file == NULL){
        printf("Error: Unable To Open File.\n");
        return;
    }
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(struct User), userCount, file);
    fclose(file);
    //printf("Saved Successfully.\n");
}

void userLogin() {
    char userId[50], userPhone[50];
    struct User *selectedUser = NULL;
    int found = 0;
    loadFile();
    do{
        system("cls");
        printf("*** He Thong Quan Ly Ngan Hang ***\n");
        printf("=====================================\n");
        printf("                DANG NHAP\n");
        printf("=====================================\n");
        
        printf("Nhap CCCD: ");
        fgets(userId, sizeof(userId), stdin);
        userId[strcspn(userId, "\n")] = '\0';
        
        printf("Nhap Mat Khau: ");
        fgets(userPhone, sizeof(userPhone), stdin);
        userPhone[strcspn(userPhone, "\n")] = '\0';

        int i;
        for(i = 0; i < userCount; i++){
            if(strcmp(users[i].userId, userId) == 0 && strcmp(users[i].userPhone, userPhone) == 0){
                selectedUser = &users[i];
                found = 1;
            break;
            }
        }

        if(found){
            userMenu(selectedUser);
            break;
        }else{
            printf("Khong Tim Thay Nguoi Dung.\n");
        }
    }while(!found);
}

void userMenu(struct User *user){
    int choice;
    do{
        system("cls");
        printf("\n*** He Thong Quan Ly Ngan Hang ***\n");
        printf("====================================\n");
        printf("[1] Thong Tin Nguoi Dung\n");
        printf("[2] Rut Tien\n");
        printf("[3] Nap Tien\n");
        printf("[0] Thoat Chuong Trinh.\n");
        printf("====================================\n");
        printf("Ban Hay Nhap Lua Chon: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                showUserInfo(user);
            break;
            case 2:
                withdrawMoney(user);
            break;
            case 3:
                depositMoney(user);
            break;
            case 0:
                printf("====== Cam On Ban =====\n====== Hen Gap Lai ====\n");
                exit(0);
            break;
            default:
                printf("Lua Chon Khong Hop Le.\n");
        }
    }while (1);
}

void showUserInfo(struct User *selectedUser){
    if(selectedUser == NULL){
        printf("Loi: Khong Co Nguoi Dung Duoc Chon.\n");
        return;
    }

    int choice;
    while(1){
        system("cls");
        printf("\n*** Menu Thong Tin Nguoi Dung ***\n");
        printf("=====================================\n");
        printf("[1] Thong Tin Tai Khoan\n");
        printf("[2] Chinh Sua Thong Tin\n");
        printf("[0] Quay Lai\n");
        printf("=====================================\n");
        printf("Ban Hay Nhap Lua Chon: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                printf("ID/CCCD: %s\n", selectedUser->userId);
                printf("Ten: %s\n", selectedUser->name);
                printf("Email: %s\n", selectedUser->email);
                printf("So Dien Thoai: %s\n", selectedUser->userPhone);
                printf("So Du: %.2f\n", selectedUser->account.balance);
                printf("Gioi Tinh: %s\n", (selectedUser->gender == 0) ? "Nu" : "Nam");
                printf("Trang Thai Tai Khoan: %s\n", (selectedUser->account.status) ? "Mo" : "Bi Khoa");
                printf("Ngay Sinh: %02d-%02d-%04d\n", selectedUser->dateOfBirth.day, selectedUser->dateOfBirth.month, selectedUser->dateOfBirth.year);
                break;
            case 2:
                while(1){
                    system("cls");
                    printf("\n*** Chinh Sua Thong Tin Nguoi Dung ***\n");
                    printf("=====================================\n");
                    printf("[1] Thay Doi Ten\n");
                    printf("[2] Thay Doi Email\n");
                    printf("[3] Thay Doi So Dien Thoai\n");
                    printf("[0] Quay Lai\n");
                    printf("=====================================\n");
                    printf("Ban Hay Nhap Lua Chon: ");
                    int editChoice;
                    scanf("%d", &editChoice);
                    getchar();

                    switch(editChoice){
					case 1:
    					while(1){
        					printf("Nhap Ten Moi: ");
        					fgets(selectedUser->name, sizeof(selectedUser->name), stdin);
        					selectedUser->name[strcspn(selectedUser->name, "\n")] = '\0';

        					int isValidName = 1;
        					int i;
        					for( i = 0; i < strlen(selectedUser->name); i++){
            				if(selectedUser->name[i] >= '0' && selectedUser->name[i] <= '9'){
                				isValidName = 0;
                				break;
            					}
        					}

        					if(isValidName){
            					printf("Cap Nhat Thanh Cong Ten Moi: %s\n", selectedUser->name);
            					break;
        					}else{
            					printf("Loi: Ten Khong Duoc Chua So. Vui Long Nhap Lai.\n");
       						 }
    					}
    				break;
					case 2:
    					while(1){
        					printf("Nhap Email Moi: ");
        					fgets(selectedUser->email, sizeof(selectedUser->email), stdin);
        					selectedUser->email[strcspn(selectedUser->email, "\n")] = '\0';

        					if(strlen(selectedUser->email) > 30){
            					printf("Loi: Email Khong Duoc Qua 30 Ky Tu. Vui Long Nhap Lai.\n");
            					continue;
       						}
        					int isDuplicate = 0;
        					int i;
       						for( i = 0; i < userCount; i++){
            				if(strcmp(users[i].email, selectedUser->email) == 0){
                				isDuplicate = 1;
                				break;
            				}
        				}
        				if(isDuplicate){
            				printf("Loi: Email Da Ton Tai. Vui Long Nhap Lai.\n");
        				}else{
            				printf("Cap Nhat Thanh Cong Email Moi: %s\n", selectedUser->email);
            				break;
       				    }
    				}
   					break;


					case 3:
   						while(1){
        					printf("Nhap So Dien Thoai Moi: ");
        					fgets(selectedUser->userPhone, sizeof(selectedUser->userPhone), stdin);
        					selectedUser->userPhone[strcspn(selectedUser->userPhone, "\n")] = '\0';

        					if(strlen(selectedUser->userPhone) != 10){
            					printf("Loi: So Dien Thoai Phai Co 10 Ky Tu. Vui Long Nhap Lai.\n");
            					continue;
        					}
        					
        					int isValidPhone = 1;
        					int i;
        					for( i = 0; i < strlen(selectedUser->userPhone); i++){
            				if(selectedUser->userPhone[i] < '0' || selectedUser->userPhone[i] > '9'){
                				isValidPhone = 0;
                				break;
            				}
        				}

        				if(isValidPhone){
            				int isDuplicate = 0;
							int i;
            				for( i = 0; i < userCount; i++){
                			if(strcmp(users[i].userPhone, selectedUser->userPhone) == 0){
                    			isDuplicate = 1;
                    			break;
                			}
            			}

            			if(isDuplicate){
                			printf("Loi: So Dien Thoai Da Ton Tai. Vui Long Nhap Lai.\n");
            			}else{
                			printf("Cap Nhat Thanh Cong So Dien Thoai Moi: %s\n", selectedUser->userPhone);
                			break;
            			}
        				}else{
            				printf("Loi: So Dien Thoai Chi Duoc Chua So. Vui Long Nhap Lai.\n");
        				}
   					 }
    				break;

                	case 0:
                        return;
                    default:
                        printf("Lua Chon Khong Hop Le.\n");
                    }
                    printf("\nNhan Phim Bat Ky De Tiep Tuc...\n");
                    getchar();
                }
                break;

            case 0:
                return;

            default:
                printf("Lua Chon Khong Hop Le. Vui Long Nhap Lai.\n");
        }
        printf("\nNhan Phim Bat Ky De Tiep Tuc...\n");
        getchar();
    }
}


void withdrawMoney(struct User *selectedUser){
    if(selectedUser == NULL){
        printf("Loi: Tai Khoan Khong Hop Le.\n");
        return;
    }

    system("cls");
    float withdrawAmount;
    printf("Nhap So Tien Can Rut: ");
    scanf("%f", &withdrawAmount);
    
    if(withdrawAmount <= 0){
        printf("Loi: So Tien Phai Lon Hon 0.\n");
    }else if (withdrawAmount > selectedUser->account.balance){
        printf("Loi: So Du Khong Du De Rut %.2f.\n", withdrawAmount);
        printf("So Du Hien Tai: %.2f.\n", selectedUser->account.balance);
    }else{
        selectedUser->account.balance -= withdrawAmount;
        printf("Rut Thanh Cong %.2f.\n", withdrawAmount);
        printf("So Du Moi: %.2f.\n", selectedUser->account.balance);
        saveFile();
    }
    printf("\nNhan Phim Bat Ky De Quay Lai...\n");
    getchar();
    getchar();
}

void depositMoney(struct User *selectedUser){
    if(selectedUser == NULL){
        printf("Loi: Tai Khoan Khong Hop Le.\n");
        return;
    }

    system("cls");
    float depositAmount;
    printf("Nhap So Tien Can Nap: ");
    scanf("%f", &depositAmount);
    
    if(depositAmount <= 0){
        printf("Loi: So Tien Phai Lon Hon 0.\n");
    }else{
        selectedUser->account.balance += depositAmount;
        printf("Nap Thanh Cong %.2f.\n", depositAmount);
        printf("So Du Moi: %.2f.\n", selectedUser->account.balance);
        saveFile();
    }
    printf("\nNhan Phim Bat Ky De Quay Lai...\n");
    getchar();
    getchar();
}
