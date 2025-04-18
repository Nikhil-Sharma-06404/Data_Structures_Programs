// // Let's start with some basics let var const 
// // let val = 1

// // for(let val=1; val<10; val++){
// //     console.log(`${val} * ${val+1} = ${val*(val+1)}`);
// // }

// // console.log(val) // Ans : 10 as var -> global scope

// // const val = new Object()
// // val.name1 = "Anonymous"
// // val.isLoggedIn = false

// // const myUser = {
// //     name : "Nikhil Sharma",
// //     age : 21,
// //     email : "nikhil@google.com",
// //     frameWorks : ["react","expressjs"],
// //     [val] : 1233
// // }

// // const obj = Object.assign({},val,myUser)
// // const object  = Object.freeze(myUser)

// // myUser.age = 34
// // console.log(myUser);
// // myUser.age = 34

// // console.log(myUser);

// function three(){
//     let value = 100;
//     const ans = Math.floor(Math.random()**value) + 1;

// return `The value of log10${value} is ${ans}`;
// }

// const first = () =>{
//      function two(){
//         const myname = "nihkil"
//         console.log(myname)
//         return true
//     }

//     if(two()){
//         console.log(three());    
//     }
// }

// first()

// To handle async tasks like db connection, network, cryptography 
// const promise = new Promise(function(resolve,reject){
//     setTimeout(function(){
//         let error = false;
//         if(!error){
//             console.log('Async Task like db connection successful !');
//             const details = {username: 'Nikhil', password: 123, age: 21, isLoggedin : true}
//             resolve(details)
//         }else{
//             reject('ERROR : SOMETHING WENT WRONG !')
//         }
//     },2000)
// })

// promise
// .then((res)=>{
//     console.log('Resolved ! User Details', res)
//     return res
// })
// .then((res) => {
//     console.log('ISLOGGEDIN : ',res.isLoggedin);
//     console.log('AGE : ', res.age)
// })
// .catch((error) => {
//     console.log(error);
// })
//;

// new Promise((resolve,reject) => {
//     setInterval(function(){
//         let error = false;
//         const userInfo = {name : 'NEXTJS', username: 'NEXTJS@134' , password : 'JAVASCRIPT'}
//         if(!error){
//             console.log('DB Connected');
//             resolve(userInfo);
//         }else{
//             reject('ERROR : DB NOT CONNECTED')
//         }
//     },2000)
// })
// .then((user)=>{
//     setInterval(()=>{
//         console.log(user);
//     },2000)
// })
// .catch((err)=>{
//     console.log(err);
// })
// .finally(()=>{
//    console.log('Promise is either Resolved or Rejected !' );
// })


// Async-await cannot directly handle errors like .then.catch in promsie chaining
// So another alternative is to use try catch block inside the async await

// async function getAllUsers(){
//     // Fetch api returns a promise can be in 3 states pending,fullfilled,rejected
//    try {
//     const response = await fetch('https://randomuser.me/api/')
//     console.log(await response.json());
//    } catch (error) {
//     console.log(error);
//    }
// }

// getAllUsers();

// fetch('https://randomuser.me/api/')
// .then((response)=>{
//    return response.json();
// })
// .then((data) => {
//     console.log(data);
// })


// Behind the Scenes : Classes are succesor of this in which proto are called method
// function UserInfo(username,password,courseName){
//        this.username = username;
//        this.password = password;
//        this.courseName = courseName;
// }

// UserInfo.prototype.encryptPassword = function(){
//     return `${this.password}abc#123`
// }

// UserInfo.prototype.CourseReview = function(){
//     return `${this.courseName} is a 4.5* Rating Course.`
// }

// const userOne = new UserInfo("Nikhil",123,'JAVASCRIPT');
// console.log(userOne.encryptPassword());
// console.log(userOne.CourseReview());


// Let's know understand how super keyword is executed using Functional object

// function setUsername(username){
//     this.username = username;
// }

// function userInfo2(username,password){
//     setUsername.call(this,username); 
//     // used to call {another function execution context} using ##current execution context
//     // Must pass this as argument so that another object properties are subtituted to current execution context object
//     this.password = password
// }

// const myUser = new userInfo2("Nikhil",12345)
// console.log(myUser);

// Object Oriented getter Setter
class JAVASCRIPT{
    constructor(email,pasword){
        this.email = email;
        this.pasword = pasword
    }

    get email(){
        return this._email.toUpperCase();
    }

    set email(value){
        this._email = value
    }
}

const user = new JAVASCRIPT("random123@ai.com","4311")
console.log(user.email);



