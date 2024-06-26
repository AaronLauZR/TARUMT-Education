//--------------- Toggle Chatbot Button ---------------
document.addEventListener("DOMContentLoaded", () => {
    const chatbotToggler = document.querySelector(".chatbot-toggler");

    chatbotToggler.addEventListener("click", () => {
        document.body.classList.toggle("show-chatbot");
    });
});

//--------------- Chatbot Conversation ---------------
const chat = {
    1: {
        text: 'Hi! Welcome to Tarumt FOCS.',
        options: [
            {
                text: '👋',
                next: 2
            }
        ]
    },
    2: {
        text: 'I am chatbot. I have here to resist you.',
        next: 3
    },
    3: {
        text: 'Do you have any questions?',
        options: [
            {
                text: "<strong>Yes</strong>, please help me!",
                next: 4
            },
            {
                text: "<strong>Nope</strong>, Everything is fine.",
                next: 5
            }
        ]
    },
    4: {
        text: 'Which question you would like to ask?',
        options: [
            {
                text: "What is the course offered",
                next: 6
            }, 
            {
                text: "When is the intake?",
                next: 7
            },
            {
                text: "What is the enrollment course?",
                next: 8
            },
            {
                text: "Who are TAR UMT Staff directory?",
                next: 9
            }
            
        ]
    },
    5: {
        text: 'Alright, if any question to ask, please don\'t hesitate to ask me!',
    },
    6: {
        text: 'To know more about the course offered..',
        options: [
            {
                text: "Go to the compare course page",
                url: "comparisonTable.html",
            }
        ]
    },
    7: {
        text: 'Our intakes are in February, June, October and November. \n The June Intakes is the Main Intake.',
    },
    8: {
        text: 'To check more about the enrollment..',
        options: [
            {
                text: "Go to the enrollment page",
                url: "enrollment2.html",
            }
        ]
    },
    9: {
        text: "About Staff Directory",
        options: [
            {
                text: "Go to staff directory",
                url: "Staff_Directory.html"
            }
        ]
    },
    11: {
        text: "For details on fees",
        options: [
            {
                text: "Go to bursary information",
                url: "https://www.tarc.edu.my/bursary/content.jsp?cat_id=5AA0377F-4E7F-494A-8EB4-CEF5CE4DD7AE"
            }
        ]
    },

    /*
    4: {
        text: 'Awesome. This chat is still in development. Happy coding!',
    },
    5: {
        text: 'Aah, you\'re missing out!',
        next: 6
    },
    6: {
        text: 'You should check it out on GitHub',
        options: [
            {
                text: "Go to GitHub",
                url: "https://github.com/peekobot/peekobot"
            }
        ]
    }
    */

    
};
