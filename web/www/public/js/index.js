window.onscroll = function() {
    var pos = document.body.scrollTop;
    document.getElementById('motivation-tab').classList.remove('navitem-selected');
    document.getElementById('solution-tab').classList.remove('navitem-selected');
    document.getElementById('features-tab').classList.remove('navitem-selected');

    console.log(pos);
    console.log(pos >= document.getElementById('motivation').offsetTop);

    if (pos >= document.getElementById('features').offsetTop)
        document.getElementById('features-tab').classList.add('navitem-selected');
    else if (pos >= document.getElementById('solution').offsetTop)
        document.getElementById('solution-tab').classList.add('navitem-selected');
    else if (pos >= document.getElementById('motivation').offsetTop)
        document.getElementById('motivation-tab').classList.add('navitem-selected');
};