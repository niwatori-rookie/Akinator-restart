var questions=[]; /*空の配列を作成*/

var tcn_qlist;
var tcn_alist;
var tcn_prop;


var yesnos = {"Doraemon":
	      {"Clever?":
	       [3,6],
	       "A woman?":
	       [8,1],
	       "transform　or metamorphose?":
	       [6,2],
	       "Too emotional?":
	       [4,6],
	       "Wear a hat?":
	       [8,1],
	       "Related to music?":
	       [8,1],
	      },
	      "Kaname Madoka":
	      {"Clever?":
	       [4,5],
	       "A woman?":
	       [1,8],
	       "transform　or metamorphose?":
	       [1,8],
	       "Too emotional?":
	       [4,6],
	       "Wear a hat?":
	       [8,1],
	       "Related to music?":
	       [7,2],
	      },
	      "Hatsune Miku":
	      {"Clever?":
	       [2,6],
	       "A woman?":
	       [1,8],
	       "transform　or metamorphose?":
	       [8,1],
	       "Too emotional?":
	       [8,1],
	       "Wear a hat?":
	       [8,1],
	       "Related to music?":
	       [1,8],
	      },
	      "Monkey D. Luffy":
	      {"Clever?":
	       [7,3],
	       "A woman?":
	       [8,1],
	       "transform　or metamorphose?":
	       [1,8],
	       "Too emotional?":
	       [1,8],
	       "Wear a hat?":
	       [1,8],
	       "Related to music?":
	       [5,4],
	      },
	      "Son Goku":
	      {"Clever?":
	       [8,1],
	       "A woman?":
	       [8,1],
	       "transform　or metamorphose?":
	       [1,8],
	       "Too emotional?":
	       [1,8],
	       "Wear a hat?":
	       [8,1],
	       "Related to music?":
	       [8,1],
	      },
	      "Light Yagami":
	      {"Clever?":
	       [1,8],
	       "A woman?":
	       [8,1],
	       "transform　or metamorphose?":
	       [8,1],
	       "Too emotional?":
	       [3,6],
	       "Wear a hat?":
	       [8,1],
	       "Related to music?":
	       [7,2],
	      },
	      "ARALE":
	      {"Clever?":
	       [4,4],
	       "A woman?":
	       [2,7],
	       "transform　or metamorphose?":
	       [6,2],
	       "Too emotional?":
	       [8,1],
	       "Wear a hat?":
	       [1,8],
	       "Related to music?":
	       [8,1],
	      }
};


var ks_info = {
    "Doraemon":{refURL : "https://en.wikipedia.org/wiki/Spaghetti",
	    refImgURL:"https://www.tv-asahi.co.jp/doraemon/cast/img/doraemon.jpg"},
    "Kaname Madoka":{refURL : "　",
	    refImgURL:"https://www.madoka-magica.com/tv/character/img/chara_thumb1.gif"},
    "Hatsune Miku":{refURL : "https://en.wikipedia.org/wiki/Coca-Cola",
	    refImgURL:"https://pics.prcm.jp/a39019c4112a0/43749441/jpeg/43749441_220x278.jpeg"},
    "Monkey D. Luffy":{refURL : "https://en.wikipedia.org/wiki/Hamburger",
	    refImgURL:"https://i.pinimg.com/736x/10/3b/3a/103b3a0a2acede04d685dc5937405db3.jpg"},
    "Son Goku":{refURL : "https://en.wikipedia.org/wiki/Pizza",
	    refImgURL:"https://vjump.shueisha.co.jp/comic/dbs03/assets/img/hero_cast.png"},
    "Light Yagami":{refURL : "https://en.wikipedia.org/wiki/Ramen",
	    refImgURL:"https://pbs.twimg.com/media/Cv70rVlVMAAwmSe.jpg"},
    "ARALE":{refURL : "https://en.wikipedia.org/wiki/Curry",
	    refImgURL:"https://i.pinimg.com/236x/67/c6/64/67c664255462fadf64228b73c467f2a1.jpg"},
};

var ks = Object.keys(yesnos);
var data_keys = Object.keys(yesnos[ks[0]]);
for(var i = 0; i < data_keys.length; i++){
    questions.push(data_keys[i]);
}

function getBestEstimate(prop){
    var maxEstimate = 0;
    var maxEstimateChara = "";
    var maxIndex = 0;

    for (var i  = 0 ; i <  ks.length; i++){
	if(maxEstimate < prop[ks[i]]){
	    maxEstimate = prop[ks[i]];
	    maxEstimateChara = ks[i];
	    maxIndex = i;
	}
    }

    return {maxest: maxEstimate, maxestchara : maxEstimateChara, maxindex:maxIndex};
}

function isLastQuestion(prop){
    var result = getBestEstimate(prop);
    if(result.maxest > 0.5){
	return {result:true, detail:result};
    }else{
	return {result:false, detail:result};
    }
}

function initProp(){
    prop = {};
    for(var i = 0; i < ks.length;i++){
	prop[ks[i]] = 1.0 / ks.length;
    }
    return prop;
}

function initGameState() {
    tcn_qlist = [];
    tcn_alist = [];
    tcn_prop = {};
    
    //初めの質問を選択
    prop = initProp();
    var q = decideQ(prop, []);
    
    var firstQuestion = {name:q.newQTitle, questionid:q.newQId};

    tcn_qlist = [firstQuestion.questionid];
    tcn_alist = [];
    tcn_prop = prop;


    $("#q").attr("questionId", firstQuestion.questionid);
    $("#q").html(firstQuestion.name+" ?");
    var candidate = "<b><u>"+ks[0];
    for(var i = 1; i < ks.length;i++){
	candidate += ", ";
	candidate += ks[i];
    }
    candidate += "</u></b>";
    $("#candidate-word").html(candidate);
};

function updateFromStart(qlist, alist, prop, ans, qId){
    var newProp = initProp();

    for (var i = 0 ; i < qlist.length; i++){

	var tmpans = alist[i];
	if(qlist[i] == qId){
	    tmpans = ans;
	}

	newProp = updateP(newProp, qlist[i], tmpans, true);

	var lastProp = isLastQuestion(newProp);
	var isFinalAns = lastProp.result;
	if(isFinalAns){
	    break;
	}
    }
    return [newProp, i];
}

function updateP(prop, qindex, a, isId){
    var new_p = {};
    var base_p = 0;  
    var q = questions[qindex];

    //あらかじめ計算可能
    for(var i = 0; i < ks.length; i++){
	var kid = ks[i];
	base_p += (yesnos[kid][q][a]/(yesnos[kid][q][0]+yesnos[kid][q][1])) * prop[kid];
    }

    for(var i = 0; i < ks.length; i++){
	var kid = ks[i];
	new_p[kid] = 1.0 / base_p * prop[kid] * (yesnos[ks[i]][q][a]/(yesnos[kid][q][0]+yesnos[kid][q][1]));
    }
    
    return new_p;
}

function calculateE(prop){
    var entropy = 0;
    for (var index = 0; index < ks.length; index++){
	entropy += - prop[ks[index]] * Math.log2(prop[ks[index]]);
    }
    return entropy;    
}

function calculateGainE(cur_e, qindex, prop){
    var w_0 = 0;

    var q = questions[qindex];
    for (var index = 0; index < ks.length; index++){
	var kid = ks[index];
	w_0 += prop[kid] * (yesnos[kid][q][0]/(yesnos[kid][q][0]+yesnos[kid][q][1]));
    }
    var p_0 = updateP(prop, qindex, 0, false);
    var e_0 = calculateE(p_0);

    var w_1 = 1 - w_0;
    
    var p_1 = updateP(prop, qindex, 1, false);
    var e_1 = calculateE(p_1);

    return cur_e - (w_0 * e_0 + w_1 * e_1);
}

function decideQ(prop, qlist){
    var qId = -1;
    var title = "";
    var max_e = -10000000;
    var max_e_q = "";
    var max_e_q_i = -1;

    var cur_entropy = calculateE(prop);

    for (var i = 0; i < questions.length; i++){
	if (qlist.includes(i)){
	    continue;
	}else{
	    var e = calculateGainE(cur_entropy, i, prop);
	    if (max_e < e){
		max_e = e;
		max_e_q = questions[i];
		max_e_q_i = i;
	    }
	}
    }

    return {newQId: max_e_q_i, newQTitle:max_e_q, newQMaxE:max_e};
}

function genSuggests(prop){
    suggests = [];

    // Create items array
    var items = Object.keys(prop).map(function(key) {
	    return [key, prop[key]];
	});

    // Sort the array based on the second element
    items.sort(function(first, second) {
	    return second[1] - first[1];
	});

    // Create a new array with only the first 5 items
    topids = items.slice(0, 3);

    for (var itemindex = 0; itemindex < topids.length; itemindex++){
	var targetindex = topids[itemindex][0];
	
	for (var kindex = 0; kindex < ks.length; kindex++){
	    if(ks[kindex] == targetindex){
		suggests.push({name:ks[kindex],
			    ansRefURL:ks_info[ks[kindex]].refURL,
			    ansRefImgURL:ks_info[ks[kindex]].refImgURL,
			    rate: topids[itemindex][1]
			});
		break;
	    }
	}
    }

    return suggests;
}

function returnResult(qlist, alist, prop, needNewQuestion, ans, qId){
    var isFinalAns = false;
    var lastProp;
    var lastIndex = -1;

    if(needNewQuestion){
	console.log(qlist.length + " : " + questions.length);
	if(qlist.length == questions.length){
	    isFinalAns = true;
	    var result = getBestEstimate(prop);
	    lastProp = {result:true, detail:result};
	}else{
	    prop = updateP(prop, qlist[qlist.length-1], ans, true);
	    lastProp = isLastQuestion(prop);
	    isFinalAns = lastProp.result;
	}
    }else{
	tmpprop = updateFromStart(qlist, alist, prop, ans, qId);
	lastProp = isLastQuestion(tmpprop[0]);
	lastIndex = tmpprop[1];
	isFinalAns = false;
    }
    
    
    var data;
    if(isFinalAns && needNewQuestion){
	var suggests = genSuggests(prop);
	data= {"isFinal":true,
	       "finalAns" : lastProp.detail,
	       "suggests":suggests
	};

	alist.push(ans);

	tcn_alist = alist;
	tcn_prop = prop;
    }else if( !needNewQuestion){
	var suggests = genSuggests(tmpprop[0]);
	data= {"isFinal":false,
	       "updateAns" : lastProp.detail,
	       "suggests":suggests,
	       "lastIndex" : lastIndex
	};

	for(var i = 0 ; i < qlist.length; i++){
	    if(qlist[i] == qId){
		alist[i] = ans;
	    }
	}

	tcn_alist = alist;
	tcn_prop = prop;
    }else{
	var suggests = genSuggests(prop);

	var q = decideQ(prop, qlist);
	var newNextQuestion = q.newQId;
	data= {"isFinal":false,
	       "nextQuestion":q.newQTitle,
	       "nextQuestionId": newNextQuestion,
	       "suggests":suggests
	};
	
	qlist.push(newNextQuestion);
	alist.push(ans);

	tcn_qlist = qlist;
	tcn_alist = alist;
	tcn_prop = prop;
    }
    
    return {"msg":"ok",  "result":data};
}


function updateYesNo (ans , qId){
    var qlist = tcn_qlist;
    var alist = tcn_alist;
    var prop  = tcn_prop;
    return returnResult(qlist, alist, prop, false, ans, qId);
};

function selectYesNo(ans){
    var qlist = tcn_qlist;
    var alist = tcn_alist;
    var prop  = tcn_prop;
    return returnResult(qlist, alist, prop, true, ans, -1);
};

function appendToSuggestZone(suggests){
    $("#suggest-knowledges-raw").html("");
    var suggestHtml = "";

    if(suggests){
	for(var i = 0; i < suggests.length; i++){
	    var specialString = "";
	    if(suggests[i]["rate"] && parseInt(suggests[i]["rate"]*100) > 1){
		specialString = "("+parseInt(suggests[i]["rate"]*100)+"%)";
	    }
	    suggestHtml += "<div class='suggest-knowledge-panel'>"
		+"<img width='120px' height='120px' src='"+suggests[i]["ansRefImgURL"]+"'></img>"
		+"<a style='color:white;text-decoration:none;' target='_blank' rel='noopener noreferrer'  href='"+suggests[i]["ansRefURL"]+"'><div>"+(i+1)+". "+suggests[i]["name"]+specialString+"</div></a>"
		+"</div>";
	}
    }
    
    $("#suggest-knowledges-raw").html(suggestHtml).hide().show("slow");
}

function addNewLineToQuestionHistory(ans, prevQuestion, qid){
    var yesno = "No";
    var yesnoclass = "q-ans-cell-no";
    if(ans > 0){
	yesno = "Yes";
	yesnoclass = "q-ans-cell-yes";
    }

    $("#q-hist-table").attr("tablenum", parseInt($("#q-hist-table").attr("tablenum"))+1);

    var newLine = "<div style='display:table-row;'><div class='index-cell'>"+
	+ $("#q-hist-table").attr("tablenum")
	+ "</div><div class='q-cell'>"
	+ prevQuestion
	+ "</div><div class='q-ans-cell " + yesnoclass + "' questionid='"+qid+"'>"
	+ yesno
	+"</div></div>";
    $("#q-hist-table").append(newLine);
}

function disableFunctions(){
    $("#yes-button").css("background-color", "gray");
    $("#no-button").css("background-color", "gray");
    $("#yes-button").css("color", "white");
    $("#no-button").css("color", "white");
    $("#reset-thothnator").css("font-size", "60px");
    $("#reset-thothnator").css("padding", "20px");
}

function answer(ans){
    var result = selectYesNo(ans);
    var target = result.result;
    var suggests = target["suggests"];
    appendToSuggestZone(suggests);
    
    //Update Question
    var prevQuestion = $("#q").html();
    var prevQid = $("#q").attr("questionId");
    if(target.isFinal){

	console.log("target");
	console.log(target);
	$("#q").html(target["finalAns"]["maxestchara"]+" !?");
	$("#q").attr("questionId", "");
	disableFunctions();
    }else{
	$("#q").html(target["nextQuestion"]);
	$("#q").attr("questionId", target["nextQuestionId"]);
    }
    
    //Add New Line to Question History
    addNewLineToQuestionHistory(ans, prevQuestion, prevQid);
}

function updateAnswer(ans, qid){
    var result = updateYesNo (ans , qid);
    var target = result.result;
    var suggests = target["suggests"];
    appendToSuggestZone(suggests);

    $(".q-ans-cell").removeClass("not-used-in-update");
    $(".q-ans-cell:gt("+target["lastIndex"]+")").addClass("not-used-in-update");

    if($("#q").attr("questionId").length == 0){
	$("#q").html(target["updateAns"]["maxestchara"]+" !?");
	$("#q").attr("questionId", "");
    }
}

$(document).ready(function(){
	initGameState();
	$(document).on('click',".q-ans-cell", function(){
		if($("#q").attr("questionId").length == 0){		    
		    var target=$($(this)[0]);
		    var ans = 0;
		    if($(this).hasClass("q-ans-cell-yes")){
			target.html("No");
		    }else{
			target.html("Yes");
			ans = 1;
		    }
		    target.toggleClass("q-ans-cell-yes");
		    target.toggleClass("q-ans-cell-no");
		    updateAnswer(ans, target.attr("questionId"));
		}
	    });
	
	$("#yes-button").on("click",function(){
		if($("#q").attr("questionId").length > 0){
		    answer(1);
		}
	    });

	$("#no-button").on("click",function(){
		if($("#q").attr("questionId").length > 0){
		    answer(0);
		}
	    });
    });
/*アキネーターの画像処理*/
class ImageFilter {
  /**
   * @param {Object} param パラメータ
   * @param {string} param.el 画像を表示する要素のセレクタ
   * @param {string} param.imageSrc 画像ファイルのURL
   * @param {number} param.width Canvasの幅
   * @param {number} param.height Canvasの高さ
   */
  constructor(param) {
    this.el = document.querySelector(param.el);
    this.src = param.imageSrc;
    this.canvasWidth = param.width || 200;
    this.canvasHeight = param.height || 200;

    this.filters = {
      'nofilter'    : this._nofilter.bind(this),
      'grayscale'   : this._grayscale.bind(this),
      'inversion'   : this._inversion.bind(this),
      'binarization': this._binarization.bind(this),
      'gamma'       : this._gamma.bind(this),
      'blur'        : this._blur.bind(this),
      'sharpen'     : this._sharpen.bind(this),
      'median'      : this._median.bind(this),
      'emboss'      : this._emboss.bind(this),
      'mosaic'      : this._mosaic.bind(this)
    };
  }

  /**
   * 初期化
   */
  init() {
    // Canvas
    
    const preview = this._createCanvas('preview');

    // 描画順調整のため遅延
    setTimeout(() => {
      
      this.el.appendChild(preview);

      
      this.draw(preview, this._nofilter);
    }, 100);

    // Radios
    const radios = document.createElement('div');
    this.el.appendChild(radios);

    Object.keys(this.filters).forEach(type => {
      const radio = this._createRadios(type, preview);
      radios.appendChild(radio);
    });
  }

  /**
   * ラジオボタンを生成する
   * @param {string} filterType this.filtersのフィルタタイプ
   * @param {HTMLCanvasElement} canvas ラジオボタンがクリックされたときにフィルタを適用するCanvas
   * @return {HTMLLabelElement} labelタグでラップしたラジオボタン
   */
  

  /**
   * Canvasを生成する
   * @param id 生成するCanvasのID
   * @return {HTMLCanvasElement} 生成したCanvas
   */
  _createCanvas(id) {
    const canvas = document.createElement('canvas');
    canvas.id = id;
    canvas.className = 'canvas'
    canvas.width = this.canvasWidth;
    canvas.height = this.canvasHeight;

    return canvas;
  }

  /**
   * Canvasに画像を描画し、フィルタを適用する
   * @param {HTMLCanvasElement} canvas 描画するCanvas
   * @param {Function} imageFilter フィルタ関数
   */
  draw(canvas, imageFilter) {
    const ctx = canvas.getContext('2d');
    ctx.clearRect(0, 0, canvas.clientWidth, canvas.clientHeight);

    const img = new Image();
    img.crossOrigin = 'anonymous';
    img.src = this.src;
    img.onload = () => {
      ctx.drawImage(img, 0, 0, this.canvasWidth, this.canvasHeight);

      const imageData = ctx.getImageData(0, 0, this.canvasWidth, this.canvasHeight);
      const data = imageData.data;

      // filter
      imageFilter(data);

      ctx.putImageData(imageData, 0, 0);
    };

  }

  //----------------------------------------------
  // フィルタ関数
  //----------------------------------------------

  /**
   * フィルタなし
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
  _nofilter(data) {
    /* nop */
    return data;
  }

  /**
   * グレースケール
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
  _grayscale(data) {
    for (let i = 0; i < data.length; i += 4) {
      // (r+g+b)/3
      const color = (data[i] + data[i+1] + data[i+2]) / 3;
      data[i] = data[i+1] = data[i+2] = color;
    }

    return data;
  }

  /**
   * 階調反転
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
  _inversion(data) {
    for (let i = 0; i < data.length; i += 4) {
      // 255-(r|g|b)
      data[i]   = Math.abs(255 - data[i])  ;
      data[i+1] = Math.abs(255 - data[i+1]);
      data[i+2] = Math.abs(255 - data[i+2]);
    }

    return data;
  }

  /**
   * 二値化
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
   _binarization(data) {
    const threshold = 255 / 2;

    const getColor = (data, i) => {
      // threshold < rgbの平均
      const avg = (data[i] + data[i+1] + data[i+2]) / 3;
      if (threshold < avg) {
        // white
        return 255;
      } else {
        // black
        return 0;
      }
    };

    for (let i = 0; i < data.length; i += 4) {
      const color = getColor(data, i);
      data[i] = data[i+1] = data[i+2] = color;
    }

    return data;
  }

  /**
   * ガンマ補正
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
  _gamma(data) {
    // 補正値（1より小さい:暗くなる、1より大きい明るくなる）
    const gamma = 2.0;
    // 補正式
    const correctify = val => 255 * Math.pow(val / 255, 1 / gamma);

    for (let i = 0; i < data.length; i += 4) {
      data[i]   = correctify(data[i]);
      data[i+1] = correctify(data[i+1]);
      data[i+2] = correctify(data[i+2]);
    }

    return data;
  }

  /**
   * ぼかし(3x3)
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
  _blur(data) {
    const _data = data.slice();
    const avgColor = (color, i) => {
      const prevLine = i - (this.canvasWidth * 4);
      const nextLine = i + (this.canvasWidth * 4);

      const sumPrevLineColor = _data[prevLine-4+color] + _data[prevLine+color] + _data[prevLine+4+color];
      const sumCurrLineColor = _data[i       -4+color] + _data[i       +color] + _data[i       +4+color];
      const sumNextLineColor = _data[nextLine-4+color] + _data[nextLine+color] + _data[nextLine+4+color];

      return (sumPrevLineColor + sumCurrLineColor + sumNextLineColor) / 9
    };

    // 2行目〜n-1行目
    for (let i = this.canvasWidth * 4; i < data.length - (this.canvasWidth * 4); i += 4) {
      // 2列目〜n-1列目
      if (i % (this.canvasWidth * 4) === 0 || i % ((this.canvasWidth * 4) + 300) === 0) {
        // nop
      } else {
        data[i]   = avgColor(0, i);
        data[i+1] = avgColor(1, i);
        data[i+2] = avgColor(2, i);
      }
    }

    return data;
  }

  /**
   * シャープ化
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
  _sharpen(data) {
    const _data = data.slice();
    const sharpedColor = (color, i) => {
      // 係数
      //  -1, -1, -1
      //  -1, 10, -1
      //  -1, -1, -1
      const sub = -1;
      const main = 10;

      const prevLine = i - (this.canvasWidth * 4);
      const nextLine = i + (this.canvasWidth * 4);

      const sumPrevLineColor = (_data[prevLine-4+color] * sub)  +  (_data[prevLine+color] * sub )  +  (_data[prevLine+4+color] * sub);
      const sumCurrLineColor = (_data[i       -4+color] * sub)  +  (_data[i       +color] * main)  +  (_data[i       +4+color] * sub);
      const sumNextLineColor = (_data[nextLine-4+color] * sub)  +  (_data[nextLine+color] * sub )  +  (_data[nextLine+4+color] * sub);

      return (sumPrevLineColor + sumCurrLineColor + sumNextLineColor) / 2
    };

    // 2行目〜n-1行目
    for (let i = this.canvasWidth * 4; i < data.length - (this.canvasWidth * 4); i += 4) {
      // 2列目〜n-1列目
      if (i % (this.canvasWidth * 4) === 0 || i % ((this.canvasWidth * 4) + 300) === 0) {
        // nop
      } else {
        data[i]   = sharpedColor(0, i);
        data[i+1] = sharpedColor(1, i);
        data[i+2] = sharpedColor(2, i);
      }
    }

    return data;
  }

  /**
   * メディアンフィルタ
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
  _median(data) {
    const _data = data.slice();
    const getMedian = (color, i) => {
      // 3x3の中央値を取得
      const prevLine = i - (this.canvasWidth * 4);
      const nextLine = i + (this.canvasWidth * 4);

      const colors = [
        _data[prevLine-4+color], _data[prevLine+color], _data[prevLine+4+color],
        _data[i       -4+color], _data[i       +color], _data[i       +4+color],
        _data[nextLine-4+color], _data[nextLine+color], _data[nextLine+4+color],
      ];

      colors.sort((a, b) => a - b);
      return colors[Math.floor(colors.length / 2)];
    };

    // 2行目〜n-1行目
    for (let i = this.canvasWidth * 4; i < data.length - (this.canvasWidth * 4); i += 4) {
      // 2列目〜n-1列目
      if (i % (this.canvasWidth * 4) === 0 || i % ((this.canvasWidth * 4) + 300) === 0) {
        // nop
      } else {
        data[i]   = getMedian(0, i);
        data[i+1] = getMedian(1, i);
        data[i+2] = getMedian(2, i);
      }
    }

    return data;
  }

  /**
   * エンボス
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
  _emboss(data) {
    const _data = data.slice();
    const embossColor = (color, i) => {
      // 係数
      //  -1,  0,  0
      //   0,  1,  0
      //   0,  0,  0
      // → + (255 / 2)

      const prevLine = i - (this.canvasWidth * 4);
      return ((_data[prevLine-4+color] * -1) + _data[i+color]) + (255 / 2);
    };

    // 2行目〜n-1行目
    for (let i = this.canvasWidth * 4; i < data.length - (this.canvasWidth * 4); i += 4) {
      // 2列目〜n-1列目
      if (i % (this.canvasWidth * 4) === 0 || i % ((this.canvasWidth * 4) + 300) === 0) {
        // nop
      } else {
        data[i]   = embossColor(0, i);
        data[i+1] = embossColor(1, i);
        data[i+2] = embossColor(2, i);
      }
    }

    return data;
  }

  /**
   * モザイク
   * @param {Array<Number>} data ImageData.dataの配列（dataを書き換える）
   */
  _mosaic(data) {
    const _data = data.slice();

    const avgColor = (i, j, color) => {
      // 3x3の平均値
      const prev = (((i - 1) * this.canvasWidth) + j) * 4;
      const curr = (( i      * this.canvasWidth) + j) * 4;
      const next = (((i + 1) * this.canvasWidth) + j) * 4;

      const sumPrevLineColor = _data[prev-4+color] + _data[prev+color] + _data[prev+4+color];
      const sumCurrLineColor = _data[curr-4+color] + _data[curr+color] + _data[curr+4+color];
      const sumNextLineColor = _data[next-4+color] + _data[next+color] + _data[next+4+color];

      return (sumPrevLineColor + sumCurrLineColor + sumNextLineColor) / 9;
    };

    // 3x3ブロックずつ色をぬる
    for (let i = 1; i < this.canvasWidth; i += 3) {
      for (let j = 1; j < this.canvasHeight; j += 3) {

        const prev = (((i - 1) * this.canvasWidth) + j) * 4;
        const curr = (( i      * this.canvasWidth) + j) * 4;
        const next = (((i + 1) * this.canvasWidth) + j) * 4;

        ['r', 'g', 'b'].forEach((_, color) => {
          data[prev-4+color] = data[prev+color] = data[prev+4+color] = avgColor(i, j, color);
          data[curr-4+color] = data[curr+color] = data[curr+4+color] = avgColor(i, j, color);
          data[next-4+color] = data[next+color] = data[next+4+color] = avgColor(i, j, color);
        });
      }
    }

    return data;
  }
}


// main
function main() {
  const imageFilter = new ImageFilter({
    el: '#app',
    imageSrc: 'https://pbs.twimg.com/media/F7QSo_wa0AAksv6?format=png&name=small',
    width: 320,
    height: 240
  });
  imageFilter.init();
}
main();




