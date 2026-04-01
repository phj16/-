<!DOCTYPE html>
<html lang="ko">
<head>
<meta charset="UTF-8">
<title>판교고 시간표</title>
<style>
  body {
    font-family: Arial, sans-serif;
    text-align: center;
    background: #f5f7fa;
  }
  h1 {
    margin-top: 30px;
  }
  input, button {
    padding: 10px;
    margin: 10px;
    font-size: 16px;
  }
  table {
    margin: 20px auto;
    border-collapse: collapse;
    width: 60%;
    background: white;
  }
  th, td {
    border: 1px solid #ccc;
    padding: 10px;
  }
  th {
    background: #4CAF50;
    color: white;
  }
</style>
</head>
<body>

<h1>📚 판교고등학교 시간표</h1>

<input type="date" id="date">
<input type="number" id="grade" placeholder="학년 (예: 1)">
<input type="number" id="class" placeholder="반 (예: 1)">
<button onclick="loadTimetable()">조회</button>

<table id="table">
  <thead>
    <tr>
      <th>교시</th>
      <th>과목</th>
    </tr>
  </thead>
  <tbody></tbody>
</table>

<script>
function loadTimetable() {
  const date = document.getElementById("date").value.replaceAll("-", "");
  const grade = document.getElementById("grade").value;
  const classNm = document.getElementById("class").value;

  const url = `https://open.neis.go.kr/hub/hisTimetable?Type=json&ATPT_OFCDC_SC_CODE=J10&SD_SCHUL_CODE=7531255&ALL_TI_YMD=${date}&GRADE=${grade}&CLASS_NM=${classNm}`;

  fetch(url)
    .then(res => res.json())
    .then(data => {
      const tbody = document.querySelector("#table tbody");
      tbody.innerHTML = "";

      const timetable = data.hisTimetable?.[1]?.row;

      if (!timetable) {
        tbody.innerHTML = "<tr><td colspan='2'>시간표 없음</td></tr>";
        return;
      }

      timetable.forEach(row => {
        const tr = document.createElement("tr");

        const period = document.createElement("td");
        period.textContent = row.PERIO;

        const subject = document.createElement("td");
        subject.textContent = row.ITRT_CNTNT;

        tr.appendChild(period);
        tr.appendChild(subject);
        tbody.appendChild(tr);
      });
    })
    .catch(err => {
      console.error(err);
      alert("데이터 불러오기 실패");
    });
}
</script>

</body>
</html>
