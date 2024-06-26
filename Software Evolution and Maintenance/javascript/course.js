document.addEventListener("DOMContentLoaded", function () {
  const courseSelectTemplate = document.querySelector("[course-select-templete]");
  const courseCardContainer = document.querySelector("[course-card-container]");
  const searchCourse = document.querySelector("[search-course]");

  let courses = [
    {
      title: "Diploma in Computer Science",
      description: "Students are trained in both theoretical knowledge and practical skills for software development, system design and related mathematical techniques. ",
      link: "diploma.html",
    },
    {
      title: "Diploma in Information Systems",
      description: "This program focuses on business information systems, providing IT and business knowledge, including system development, management, accounting, and practical skills.",
      link: "diploma.html",
    },
    {
      title: "Diploma in Information Technology",
      description: "This program imparts essential computing skills for modern organizations, covering programming, databases, and IT principles, preparing graduates for various roles.",
      link: "diploma.html",
    },
    {
      title: "Diploma in Software Engineering",
      description: "This program offers software engineering knowledge, analytical thinking, managerial skills, and fosters innovation for future opportunities in the field.",
      link: "diploma.html",
    },
    {
      title: "Bachelor of Science (Honours) in Management Mathematics with Computing",
      description: "This program combines Management Mathematics, Computing, and Economics/Accounting, offering skills in math, computing, and preparing for diverse academic and professional pursuits.",
      link: "bachelor.html",
    },
    {
      title: "Bachelor of Computer Science (Honours) in Interactive Software Technology",
      description: "This program focuses on computer science, emphasizing interactive software development for various applications, including games, simulations, and educational tools. Students study a range of relevant subjects and can choose electives for specialization.",
      link: "bachelor.html",
    },
    {
      title: "Bachelor of Software Engineering (Honours)",
      description: "This program focuses on implementing enterprise information systems, integrating various business functions to enhance organizational performance. It covers core computing and specialized subjects, offering electives and industrial training for practical experience and improved employment prospects.",
      link: "bachelor.html",
    },
    {
      title: "Bachelor of Computer Science (Honours) in Data Science",
      description: "This program combines computer science and data science, preparing graduates for in-demand roles in data analysis and AI. It covers various specialized courses and offers real-world experience through industrial training, including a SAS Joint Certificate in Data Science and Machine Learning upon completion.",
      link: "bachelor.html",
    },
  ];

  function openCourseLink(link) {
    window.open(link, "_blank");
  }

  function addPointerClass(event) {
    event.target.classList.add("pointer");
  }

  function removePointerClass(event) {
    event.target.classList.remove("pointer");
  }

  searchCourse.addEventListener("input", (e) => {
    const value = e.target.value.toLowerCase();
    courses.forEach((course) => {
      const isVisible =
        course.title.toLowerCase().includes(value)
      course.element.classList.toggle("hide", !isVisible);
    });
  });

  courses.forEach((course) => {
    const card = courseSelectTemplate.content.cloneNode(true).children[0];
    const title = card.querySelector("[course-header]");
    const description = card.querySelector("[course-body]");

    title.textContent = course.title;
    description.textContent = course.description;

    card.addEventListener("click", () => {
      openCourseLink(course.link);
    });

    card.addEventListener("mouseenter", addPointerClass);
    card.addEventListener("mouseleave", removePointerClass);

    courseCardContainer.append(card);
    course.element = card;
  });
});
