<head>
  <script src="https://code.jquery.com/jquery-3.1.1.min.js" crossorigin="anonymous"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/tether/1.4.0/js/tether.min.js" integrity="sha384-DztdAPBWPRXSA/3eYEEUWrWCy7G5KFbe8fFjk5JAIxUYHKkDx6Qin1DkWx51bBrb" crossorigin="anonymous"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/js/bootstrap.min.js" integrity="sha384-vBWWzlZJ8ea9aCX4pEW3rVHjgjt7zpkNpZk+02D9phzyeVkE+jo0ieGizqPLForn" crossorigin="anonymous"></script>

  <script src="thothnator.js"></script>

  <style>
   
.suggest-knowledge-zone{
margin:30px auto 20px auto;
border-radius: 30px;
padding:20px;
width:95%;
background-color:white;
}

.suggest-knowledges-header{
color:rgb(197, 44, 44);
font-size:15px;
font-weight:bold;
text-align:left;
font-family: cursive;
padding:5px;
}

.suggest-knowledges{
overflow-x:auto;
overflow-y:hidden;
white-space:nowrap;
}

.suggest-knowledge{
margin:auto 10px;
box-shadow:3px 3px 3px rgba(0, 0, 0, 0.2);
background-color:white;
height:100%;
}

.suggest-knowledge-panel{
display:inline-block;
box-shadow:3px 3px 3px rgba(0, 0, 0, 0.2);
background-color:rgb(52, 56, 60);
width:140px;
height:182px;
vertical-align:top;
 white-space:normal;
margin:5px;
padding:3px;
color:white;
font-weight:bold;
font-size:14px;
text-align:center;
}

.q-cell{
display:table-cell;
width:70%;
color:white;
background-color:rgb(52, 56, 60);
border: solid 1px white;
vertical-align:middle;
font-weight:bold;
}

.index-cell{
display:table-cell;
width:5%;
color:black;
background-color:white;
border: solid 1px white;
vertical-align:middle;
font-weight:bold;
}

.q-ans-cell{
display:table-cell;
width:30%;
font-weight:bold;
font-size:30px;
border: solid 1px white;
transition: all .2s ease-in-out;
cursor:pointer;
}

.q-ans-cell-yes{
background-color:rgb(105, 211, 101);
}

.q-ans-cell-no{
background-color:rgb(243, 83, 65);
}

.q-ans-cell:hover{
background-color:rgb(89, 140, 255);
}


.not-used-in-update{
background-color:gray;
 }
 
 
 
    
   </style>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  
  <link rel="stylesheet" href="persona5.css">
 </head>
 <body>
	<img src="./images/aki.png" alt="" /> 
   <h1 style="margin:auto;width:100%;text-align:center;">Question</h1>
   <div style="width:100%; text-align:center;">
   word candidate, please choose from below words and start questions:<br>
     <div id="candidate-word"></div></div>
    
  <div class="container">
  <div class="message-window">

  <div class="message-area">
        <div class="content">
            <div class="arrow-white">
            </div>
            <div class="arrow-black">
            </div>

            <div class="background-white">
            </div>
            <div class="background-black">
            </div>
            <div class="text-area">
               <div id="q" questionid="" style="width:100%;font-size:20px; font-weight:bold;text-align:right;">
  </div>
                
            </div>
        </div>
    </div>
</div>
  </div>
  
  
  
   
  
  
  
  
  
  
  
  
  
  
  
 
  
<div class="container">
<div id="app"></div>
</div>

  <div style="display:table;width:80%;margin:20px auto;">
    <div style="display:table-cell;width:50%;">
      <div id="yes-button"  style="cursor:pointer;font-size:30px;background-color:#70e270;text-align:center;">Yes</div>
    </div>
    <div style="display:table-cell;width:50%;">
      <div id="no-button" style="cursor:pointer;border:none;font-size:30px;background-color:#ff6565;text-align:center;">No</div>
    </div>
  </div>
  
  <div class="suggest-knowledge-zone" style="">
    <div class="suggest-knowledges-header">Suggested</div>
    <div class="suggest-knowledges" id="suggest-knowledges-raw">
    </div>
  </div>
  
  
  <div style="margin:30px auto 50px auto;">
    <div style="font-family: cursive;font-weight:bold;font-size:24px;">Question and Answer History
      <div style="font-size:12px;color:gray">
	Yes/Noを押すと再度計算し直します.しかし、質問の順番は変更できません.
      </div>
    </div>
    <div id="q-hist-table" style="display:table;width:100%;border: solid 1px white; border-collapse: collapse;" tablenum="0">
    </div>
  </div>
  <a href="http://urusulambda.com/2019/03/22/%E3%82%A2%E3%82%AD%E3%83%8D%E3%83%BC%E3%82%BF%E3%83%BC%E3%81%AE%E5%AE%9F%E8%A3%85%E6%96%B9%E6%B3%95%E3%81%8C%E3%82%88%E3%81%8F%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%91%E3%81%A9%E3%80%81/" target="_blank">参考サイト</a>
 
 
 <div class="container">
 <div class="columns">
 <div class="column is-half">
  <form action="https://api.staticforms.xyz/submit" method="post" id="staticform">
  
  
  <input type="hidden" name="accessKey" value="a58e4737-2aaa-4c39-b1c8-a4f90b7562bc">
        <input type="hidden" name="subject" value="Test from Akinator">
 
  <input type="hidden" name="redirectTo" value="https://docs.google.com/forms/d/e/1FAIpQLSdqDJpdMHK_B4cT_19kGXHlNs-UrYsKB-_VbMUPZYmoT1W8vg/alreadyresponded">
  
   <div style="font-size:20px;color:gray">
	---------お問い合わせフォーム.-----------------
      </div>
  <div class="field">
          <label class="label">Name</label>
          <div class="control">
            <input class="input" type="text" name="name" placeholder="Enter Your Name" required>
          </div>
        </div>
 
 
 
 
 
  <fieldset>
    <legend><p>
    Q.あなたが予想していた通りの結果が出ましたか？
    </p></legend>
    <div>
      <input type="radio" id="contactChoice1" name="name" value="でました" />
      <label for="contactChoice1"><p>
      でました
      </p></label>
      <input type="radio" id="contactChoice2" name="name" value="でませんでした" />
      <label for="contactChoice2"><p>
      でませんでした
      </p></label>
    </div>
     </fieldset>
        
 

       
   
        <div class="field">
          <label class="label">Message</label>
          <div class="control">
            <textarea class="textarea" name="message" placeholder="Enter Your Message" required></textarea>
          </div>
        </div>
        
    
        <button class="button is-primary" type="Submit">送信</button>
        <div style="font-size:20px;color:gray">
	  ----------------------------------------------------
      </div>
 </form>
 </div>
 </div>
 </div>
 
 <div>
 <a class="btn btn-info" href="#">Topに戻る</a>
 </div> 
   
</body>
