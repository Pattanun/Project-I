const express = require('express')
const app = express()
const cors = require('cors');
const PORT = 8000
let tasks = [
    { id: 1, name: 'KAOYOD', weight : '4500' ,picture:'https://www.mokkalana.com/wp-content/uploads/2019/06/3-23.jpg'},
    { id: 2, name: 'CHUTPETCH', weight : '3500' ,picture:'https://cms.dmpcdn.com/horoscope/2020/03/26/4e818560-6f1c-11ea-b8a2-09037777d4af_original.jpg'},
    { id: 3, name: 'HATAEW', weight : '3500' ,picture:'https://cms.dmpcdn.com/horoscope/2020/03/26/4dddf260-6f1c-11ea-a7cd-dd316e61efc7_original.jpg'}
]
app.use(cors())

app.get('/', (req, res) => {
    res.json(tasks)
})

app.listen(PORT, () => console.log(`listen at ${PORT}`))