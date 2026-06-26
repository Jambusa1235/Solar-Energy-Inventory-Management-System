#include <stdio.h>
#include <string.h>
struct product{
char productName[50];
char brandName[50];
int serialNumber;
int quantity;
float unitPrice;
char productType[30];
};
struct product L[100];
int count=0;
FILE*file;

int main()
{
    int Choice;
    int serial, saleQty, i, found;

    file = fopen("solar_inventory.dat", "rb");
    while (fread(&L[count], sizeof(struct product), 1, file)==1){
        count++;
    }
    fclose(file);

  do{
    printf("\n====SOLAR ENERGY INVENTORY SYSTEM====\n");
    printf("1. AddProduct\n");
    printf("2. RecordSale\n");
    printf("3. SearchProduct\n");
    printf("4. Display All Product\n");
    printf("5. Exit\n");
    printf("Enter Choice:\n");
    scanf("%d", &Choice);

    switch(Choice){
    case 1:
        printf("\nEnter Product Name:\n");
        scanf("%s", L[count].productName);

        printf("Enter Brand Name:\n");
        scanf("%s", L[count].brandName);

        printf("Enter Serial Number:\n");
        scanf("%d", &L[count].serialNumber);

        printf("Enter Quantity:\n");
        scanf("%d", &L[count].quantity);

        printf("Enter Unit Price:\n");
        scanf("%f", &L[count].unitPrice);

        printf("Enter Product Type(Solar Panel/Inverter/Lithium Battery):\n");
        scanf("%s", L[count].productType);

        file = fopen("solar_inventory.dat","ab");
        if(file != NULL){
        fwrite(&L[count], sizeof(struct product), 1, file);
        fclose(file);
        printf("\nProduct Added Successfully and Saved to Inventory.dat!\n");
        }else{
        printf("Error Saving Product!\n");
        }

        count++;
        break;

        case 2:
             found=0;

            printf("\nEnter Serial Number:\n");
            scanf("%d", &serial);

            for(i=0; i<count;i++)
                if(L[i].serialNumber==serial){
                    found=1;

                    printf("Enter Quantity Sold:\n");
                    scanf("%d", &saleQty);

                    if(saleQty>L[i].quantity){
                        printf("Sale exceeds available stock!\n");
                    }else{
                    L[i].quantity=L[i].quantity-saleQty;
                    printf("Sale recorded Successfully!\n");
                    if(L[i].quantity<5){
                        printf("LOW STOCK ALERT!\n");
                    }
                    file = fopen("solar_inventory.dat", "wb");
                    if (file != NULL){
                        fwrite(L, sizeof(struct product), count, file);
                        fclose(file);
                        printf("Inventory Updated in Solar_inventory.dat!\n ");
                    }
                    }

        if(found == 0){
            printf("Product Not Found\n");
        }
            break;

        case 3:
            found=0;
            printf("\nEnter Serial Number to Search:\n");
            scanf("%d", &serial);

            char brandSearch[50];
            printf("\nEnter Brand Name to Search:\n");
            scanf("%s", brandSearch);

            for(i=0;i<count;i++){
                    if((serial != 0 && L[i].serialNumber == serial)||
                       (strcmp(brandSearch, "none") != 0 && strcmp(L[i].brandName, brandSearch) == 0)){
                found=1;

                printf("\nProduct Found\n");
                printf("Name: %s\n", L[i].productName);
                printf("Brand: %s\n", L[i].brandName);
                printf("Quantity: %d\n", L[i].quantity);
                printf("Price: %2f\n", L[i].unitPrice);
                printf("Type: %s\n", L[i].productType);
            }

            }
        if(found==0){
            printf("Product Not Found!\n");
            break;

        case 4:
            if(count == 0){
                printf("\nNo Products in inventory!\n");
            }else{
            printf("\n==All PRODUCTS==\n");

            for(int i=0;i<count;i++){
            printf("\nProduct%d\n",i+1);
            printf("1. Name: %s\n", L[i].productName);
            printf("2. Brand: %s\n", L[i].brandName);
            printf("3. serial: %d\n", L[i].serialNumber);
            printf("4. Quantity: %d\n", L[i].quantity);
            printf("5. Price: %.2f\n", L[i].unitPrice);
            printf("6. Type: %s\n", L[i].productType);
            }
            }
            break;

        case 5:
            printf("\nProgram Exited Successfully.\n");
            printf("\nName:OWORI JAMES.\n");
            printf("\nReg NO:2025/DCS/DAY/0516.\n");
            break;

            default:
                printf("Invalid Choice!\n");
                break;
        }
                }
    }

  }

 while(Choice!=5);
    return 0;
  }

