const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

class ListManagementSystem {
    constructor() {
        this.itemList = [];
    }

    addItem(item) {
        this.itemList.push(item);
        console.log(`${item} has been added to the list.`);
    }

    removeItem(item) {
        const index = this.itemList.indexOf(item);
        if (index > -1) {
            this.itemList.splice(index, 1);
            console.log(`${item} has been removed from the list.`);
        } else {
            console.log(`${item} is not in the list.`);
        }
    }

    displayList() {
        if (this.itemList.length === 0) {
            console.log("The list is empty.");
        } else {
            console.log("List items:");
            this.itemList.forEach(item => {
                console.log(`- ${item}`);
            });
        }
    }
}

const listManager = new ListManagementSystem();

function main() {
    function prompt() {
        readline.question(`\nChoose an option:
1. Add item
2. Remove item
3. Display list
4. Exit
`, (choice) => {
            switch (choice) {
                case '1':
                    readline.question("Enter item to add: ", (addItem) => {
                        listManager.addItem(addItem);
                        prompt(); 
                    });
                    break;
                case '2':
                    readline.question("Enter item to remove: ", (removeItem) => {
                        listManager.removeItem(removeItem);
                        prompt(); 
                    });
                    break;
                case '3':
                    listManager.displayList();
                    prompt(); 
                    break;
                case '4':
                    console.log("Exiting the List Management System. Goodbye!");
                    readline.close();
                    process.exit(0);
                default:
                    console.log("Invalid choice. Please choose a valid option.");
                    prompt(); 
            }
        });
    }

    prompt(); 
}

main();
